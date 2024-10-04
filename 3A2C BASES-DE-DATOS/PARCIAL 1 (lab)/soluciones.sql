-- PARCIAL 1 LAB BDD 2024, Tomás Achával
-- Ejercicio 1
SELECT properties.*
FROM properties
LEFT JOIN reviews
ON properties.id = reviews.property_id
AND YEAR(reviews.created_at) = 2024
GROUP BY properties.id
ORDER BY COUNT(*) DESC LIMIT 7;

-- Ejercicio 2
-- Funcion auxiliar para el ejercicio
DELIMITER //
CREATE FUNCTION total_income (
	prop_id INT
) RETURNS DECIMAL(10,2)
READS SQL DATA
BEGIN
	DECLARE night_price DECIMAL(10,2) DEFAULT 0;
	DECLARE total DECIMAL(10,2) DEFAULT 0;
    
    SELECT price_per_night INTO night_price
    FROM properties WHERE id = prop_id;

    SELECT 
		sum(DATEDIFF(b.check_out, b.check_in))*night_price
    INTO total
    FROM bookings AS b
    WHERE b.property_id = prop_id
    GROUP BY b.property_id;
    
    RETURN total;
END //
DELIMITER ;

SELECT p.*, total_income(p.id) as total_income
FROM properties as p;

-- Ejercicio 3
SELECT users.*
FROM users INNER JOIN payments
ON users.id = payments.user_id
GROUP BY users.id
ORDER BY sum(payments.amount) DESC
LIMIT 10;

-- Ejercicio 4
DELIMITER //
CREATE TRIGGER notify_host_after_booking
AFTER INSERT ON bookings
FOR EACH ROW
BEGIN
	INSERT INTO messages
         (sender_id, receiver_id, property_id, content, sent_at)
    SELECT NEW.user_id,
            p.owner_id,
            NEW.property_id,
            'Este usuario ha creado una reserva en tu propiedad!',
            NOW()
	FROM properties AS p
    WHERE p.id = NEW.property_id;
END //
DELIMITER ;

-- Ejercicio 5
-- total_price insertado como 0 debido a que no puede ser NULL
DELIMITER //
CREATE PROCEDURE add_new_booking (
	IN prop_id INT,
    IN u_id INT,
    IN chk_in DATE,
    IN chk_out DATE
)
BEGIN
	-- Verificar si la propiedad está disponible en las fechas solicitadas.
	IF (EXISTS 
			(SELECT 1
			FROM property_availability AS pa
			WHERE pa.property_id = prop_id
            AND pa.`status` = 'available'
			AND chk_in BETWEEN pa.available_from AND pa.available_to
			AND chk_out BETWEEN pa.available_from AND pa.available_to)
	) THEN
        -- Agregar la reserva en caso de que SI esté disponible.
		INSERT INTO bookings
			(property_id, user_id, check_in, check_out, total_price, created_at)
		VALUES (prop_id, u_id, chk_in, chk_out, 0, NOW());
	END IF;
END //
DELIMITER ;

-- Ejercicio 6
CREATE ROLE `admin`;
GRANT CREATE ON airbnb_like_db.properties TO `admin`;
GRANT UPDATE (`status`) ON airbnb_like_db.property_availability TO `admin`;

-- Ejercicio 7
-- Por que la propiedad de durabilidad hace referencia a la 
-- durabilidad de los EFECTOS de una transacción, 
-- no de los datos de la base.

