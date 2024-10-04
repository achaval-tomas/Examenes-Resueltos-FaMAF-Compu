DROP DATABASE  IF EXISTS `airbnb_like_db`;
CREATE DATABASE `airbnb_like_db` DEFAULT CHARACTER SET utf8mb4;

USE `airbnb_like_db`;

DROP TABLE IF EXISTS airbnb_like_db.users;

-- Create table for users
CREATE TABLE airbnb_like_db.users (
    id INT NOT NULL AUTO_INCREMENT,
    name VARCHAR(100) NOT NULL,
    email VARCHAR(100) UNIQUE NOT NULL,
    password VARCHAR(100) NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    CONSTRAINT pk_users PRIMARY KEY (id)
);

DROP TABLE IF EXISTS airbnb_like_db.properties;
-- Create table for properties
CREATE TABLE airbnb_like_db.properties (
    id INT NOT NULL AUTO_INCREMENT,
    owner_id INT NOT NULL,
    name VARCHAR(100) NOT NULL,
    description TEXT,
    location VARCHAR(255) NOT NULL,
    price_per_night NUMERIC(10, 2) NOT NULL,
    max_guests INT NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    CONSTRAINT pk_properties PRIMARY KEY (id),
    CONSTRAINT fk_properties_owner FOREIGN KEY (owner_id) REFERENCES users (id) ON DELETE CASCADE
);

DROP TABLE IF EXISTS airbnb_like_db.bookings;

-- Create table for bookings
CREATE TABLE airbnb_like_db.bookings (
    id INT NOT NULL AUTO_INCREMENT,
    property_id INT NOT NULL,
    user_id INT NOT NULL,
    check_in DATE NOT NULL,
    check_out DATE NOT NULL,
    total_price NUMERIC(10, 2) NOT NULL,
    status VARCHAR(50) DEFAULT 'pending',  -- 'pending', 'confirmed', 'cancelled'
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    CONSTRAINT pk_bookings PRIMARY KEY (id),
    CONSTRAINT fk_bookings_property FOREIGN KEY (property_id) REFERENCES properties (id) ON DELETE CASCADE,
    CONSTRAINT fk_bookings_user FOREIGN KEY (user_id) REFERENCES users (id) ON DELETE CASCADE
);

DROP TABLE IF EXISTS airbnb_like_db.reviews;

-- Create table for reviews
CREATE TABLE airbnb_like_db.reviews (
    id INT NOT NULL AUTO_INCREMENT,
    booking_id INT NOT NULL,
    user_id INT NOT NULL,
    property_id INT NOT NULL,
    rating INT CHECK (rating >= 1 AND rating <= 5),
    comment TEXT,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    CONSTRAINT pk_reviews PRIMARY KEY (id),
    CONSTRAINT fk_reviews_booking FOREIGN KEY (booking_id) REFERENCES bookings (id) ON DELETE CASCADE,
    CONSTRAINT fk_reviews_user FOREIGN KEY (user_id) REFERENCES users (id) ON DELETE CASCADE,
    CONSTRAINT fk_reviews_property FOREIGN KEY (property_id) REFERENCES properties (id) ON DELETE CASCADE
);

DROP TABLE IF EXISTS airbnb_like_db.property_photos;

-- Create table for property_photos
CREATE TABLE airbnb_like_db.property_photos (
    id INT NOT NULL AUTO_INCREMENT,
    property_id INT NOT NULL,
    photo_url VARCHAR(255) NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    CONSTRAINT pk_property_photos PRIMARY KEY (id),
    CONSTRAINT fk_property_photos_property FOREIGN KEY (property_id) REFERENCES properties (id) ON DELETE CASCADE
);

DROP TABLE IF EXISTS airbnb_like_db.favorites;

-- Create table for favorites
CREATE TABLE airbnb_like_db.favorites (
    user_id INT NOT NULL,
    property_id INT NOT NULL,
    CONSTRAINT pk_favorites PRIMARY KEY (user_id, property_id),
    CONSTRAINT fk_favorites_user FOREIGN KEY (user_id) REFERENCES users (id) ON DELETE CASCADE,
    CONSTRAINT fk_favorites_property FOREIGN KEY (property_id) REFERENCES properties (id) ON DELETE CASCADE
);

DROP TABLE IF EXISTS airbnb_like_db.payments;

-- Create table for payments
CREATE TABLE airbnb_like_db.payments (
    id INT NOT NULL AUTO_INCREMENT,
    booking_id INT NOT NULL,
    user_id INT NOT NULL,
    amount NUMERIC(10, 2) NOT NULL,
    payment_method VARCHAR(50) NOT NULL, -- 'credit_card', 'paypal', etc.
    payment_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    status VARCHAR(50) DEFAULT 'completed',  -- 'pending', 'completed', 'failed'
    CONSTRAINT pk_payments PRIMARY KEY (id),
    CONSTRAINT fk_payments_booking FOREIGN KEY (booking_id) REFERENCES bookings (id) ON DELETE CASCADE,
    CONSTRAINT fk_payments_user FOREIGN KEY (user_id) REFERENCES users (id) ON DELETE CASCADE
);

DROP TABLE IF EXISTS airbnb_like_db.amenities;

-- Create table for amenities (property services/features)
CREATE TABLE airbnb_like_db.amenities (
    id INT NOT NULL AUTO_INCREMENT,
    name VARCHAR(100) NOT NULL,
    CONSTRAINT pk_amenities PRIMARY KEY (id)
);

DROP TABLE IF EXISTS airbnb_like_db.property_amenities;

-- Create table for property_amenities (associating properties with amenities)
CREATE TABLE airbnb_like_db.property_amenities (
    property_id INT NOT NULL,
    amenity_id INT NOT NULL,
    CONSTRAINT pk_property_amenities PRIMARY KEY (property_id, amenity_id),
    CONSTRAINT fk_property_amenities_property FOREIGN KEY (property_id) REFERENCES properties (id) ON DELETE CASCADE,
    CONSTRAINT fk_property_amenities_amenity FOREIGN KEY (amenity_id) REFERENCES amenities (id) ON DELETE CASCADE
);

DROP TABLE IF EXISTS airbnb_like_db.messages;

-- Create table for messages
CREATE TABLE airbnb_like_db.messages (
    id INT NOT NULL AUTO_INCREMENT,
    sender_id INT NOT NULL,
    receiver_id INT NOT NULL,
    property_id INT NOT NULL,
    content TEXT NOT NULL,
    sent_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    CONSTRAINT pk_messages PRIMARY KEY (id),
    CONSTRAINT fk_messages_sender FOREIGN KEY (sender_id) REFERENCES users (id) ON DELETE CASCADE,
    CONSTRAINT fk_messages_receiver FOREIGN KEY (receiver_id) REFERENCES users (id) ON DELETE CASCADE,
    CONSTRAINT fk_messages_property FOREIGN KEY (property_id) REFERENCES properties (id) ON DELETE CASCADE
);

DROP TABLE IF EXISTS airbnb_like_db.property_availability;

-- Create table for property_availability
CREATE TABLE airbnb_like_db.property_availability (
    id INT NOT NULL AUTO_INCREMENT,
    property_id INT NOT NULL,
    available_from DATE NOT NULL,
    available_to DATE NOT NULL,
    status VARCHAR(50) DEFAULT 'available', -- 'available', 'blocked'
    CONSTRAINT pk_property_availability PRIMARY KEY (id),
    CONSTRAINT fk_property_availability_property FOREIGN KEY (property_id) REFERENCES properties (id) ON DELETE CASCADE
);
