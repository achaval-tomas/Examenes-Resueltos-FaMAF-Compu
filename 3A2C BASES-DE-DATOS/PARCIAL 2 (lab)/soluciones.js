use("university")


// Ejercicio 1
db.grades.find(
    {
        scores: {
            $not: {
                $elemMatch: {
                    type: 'homework',
                    score: { $lt: 60 }
                }
            },
            $elemMatch: {
                $or: [
                    { type: 'exam', score: { $gte: 80 } },
                    { type: 'quiz', score: { $gte: 90 } }
                ]
            }
        }
    },
    {
        _id: 0
    }
)


// Ejercicio 2
db.grades.aggregate([
    {
        $match: {
            class_id: { $in: [20, 220, 420] }
        }
    },
    {
        $project: {
            _id: 0,
            student_id: 1,
            class_id: 1,
            min_score: { $min: "$scores.score" },
            max_score: { $max: "$scores.score" },
            avg_score: { $avg: "$scores.score" },
        }
    },
    { $sort: { student: 1, class: 1 } }
])


// Ejercicio 3
db.grades.aggregate([
    {
        $project: {
            class_id: 1,
            exam_scores: {
                $filter: {
                    input: "$scores",
                    as: "score",
                    cond: { $eq: ["$$score.type", "exam"] }
                }
            }
            ,
            quiz_scores: {
                $filter: {
                    input: "$scores",
                    as: "score",
                    cond: { $eq: ["$$score.type", "quiz"] }
                }
            }
        }
    },
    { $unwind: "$exam_scores" },
    { $unwind: "$quiz_scores" },
    {
        $group: {
            _id: "$class_id",
            max_exam_score: {
                $max: "$exam_scores.score"
            },
            max_quiz_score: {
                $max: "$quiz_scores.score"
            }
        }
    },
    { $sort: { _id: 1 } }
])


// Ejercicio 4
// Promedio de promedios por clase
db.createView(
    "top10students",
    "grades",
    [
        {
            $group: {
                _id: "$student_id",
                avg_score_per_class: {
                    $addToSet: {
                        class: "$class_id",
                        avg_score: { $avg: "$scores.score" }
                    }
                }
            }
        },
        {
            $project: {
                _id: 0,
                student: "$_id",
                avg_score: {
                    $avg: "$avg_score_per_class.avg_score"
                }
            }
        },
        { $sort: { avg_score: -1 } },
        { $limit: 10 },
    ]
)


// Ejercicio 5
db.grades.updateMany(
    { class_id: 339 },
    [
        {
            $set: {
                score_avg: { $avg: "$scores.score" },
                letter: {
                    $switch: {
                        branches: [
                            {
                                case: { $lt: ["$score_avg", 60] },
                                then: "NA"
                            },
                            {
                                case: {
                                    $and: [{ $gte: ["$score_avg", 60] }, { $lt: ["$score_avg", 80] }]
                                },
                                then: "A"
                            },
                            {
                                case: { $gte: ["$score_avg", 80] },
                                then: "P"
                            }
                        ],
                        default: "",
                    }
                }
            }
        }
    ]
)


// Ejercicio 6a
/* 
    Un documento de la colección grades deberá tener los campos student_id, scores y class_id.
        student_id y class_id deben ser valores enteros.
        scores debe ser un arreglo compuesto de objetos con campos type y score.
        scores.type debe ser "exam", "quiz" o "homework".
        scores.score debe ser un double en [0, 100].
*/
db.runCommand({
    collMod: "grades",
    validator: {
        $jsonSchema: {
            required: ["student_id", "scores", "class_id"],
            properties: {
                student_id: { bsonType: "int" },
                scores: {
                    bsonType: "array",
                    items: {
                        bsonType: "object",
                        required: ["type", "score"],
                        properties: {
                            type: { enum: ["exam", "quiz", "homework"] },
                            score: {
                                bsonType: "double",
                                minimum: Double(0),
                                maximum: Double(100)
                            }
                        }
                    }
                },
                class_id: { bsonType: "int" }
            }
        },
    }
})

// Ejercicio 6b dos fallas y un éxito

// Primer falla -> campo 'score' del primer subdocumento en la lista 'scores' es string en lugar de double
db.grades.insertOne({
    student_id: 100,
    class_id: 120,
    scores: [
        { type: "exam", score: "P" },
        { type: "quiz", score: 99.1 }
    ]
})

// Segunda falla -> campo 'student_id' string en lugar de int
db.grades.insertOne({
    student_id: '100',
    class_id: 120,
    scores: [
        { type: "exam", score: 10.3 },
        { type: "quiz", score: 99.1 }
    ]
})

/* 
Otros casos de falla posibles: 
    - score no está entre 0 y 100
    - class_id no es int
    - scores.type no está en ["exam", "quiz", "homework"]
    - ...
*/

// Éxito
db.grades.insertOne({
    student_id: 100,
    class_id: 120,
    scores: [
        { type: "exam", score: 10.3 },
        { type: "quiz", score: 99.1 }
    ]
})