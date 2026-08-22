# Hotel Room Booking System — Requirement Specification & Design

## 1. Functional Requirements

### 1.1 Guest / Customer
- **FR1.1** – Register account / Log in / Log out
- **FR1.2** – Search available rooms by check-in date, check-out date, room type, number of guests
- **FR1.3** – View room details (price, amenities, photos, capacity)
- **FR1.4** – Book a room (select room, enter details, confirm booking)
- **FR1.5** – Make payment (online or at the front desk)
- **FR1.6** – View / edit / cancel an existing booking
- **FR1.7** – Receive booking confirmation via email/notification
- **FR1.8** – Rate and review after stay (optional)

### 1.2 Receptionist
- **FR2.1** – View list of bookings by date
- **FR2.2** – Check-in / Check-out guests
- **FR2.3** – Create walk-in bookings directly
- **FR2.4** – Update room status (available, occupied, cleaning, maintenance)
- **FR2.5** – Process payments and issue invoices

### 1.3 Admin / Manager
- **FR3.1** – Manage rooms (add/edit/delete room types, prices, amenities)
- **FR3.2** – Manage staff accounts and permissions
- **FR3.3** – View revenue reports and occupancy rate
- **FR3.4** – Manage promotions/discounts

### 1.4 System
- **FR4.1** – Automatically check room availability to prevent overbooking
- **FR4.2** – Send check-in/check-out reminder notifications

---

## 2. Non-Functional Requirements

- **NFR2.1** – **Performance:** The system must return room search results within 2-3 seconds under normal load
- **NFR2.2** – **Security:** User passwords must be hashed; payment information must follow basic security standards
- **NFR2.3** – **Scalability:** The system should support adding more hotels/branches in the future
- **NFR2.4** – **Reliability:** Double booking of the same room must never occur under any circumstances
- **NFR2.5** – **Availability:** The system should operate 24/7 with minimal downtime
- **NFR2.6** – **Usability:** The interface must be simple and easy to use for both customers and receptionists
- **NFR2.7** – **Maintainability:** Code should be organized following a clear architecture (e.g. MVC) for easy modification and extension
- **NFR2.8** – **Compatibility:** The web interface must work well on major browsers (Chrome, Edge, Firefox)

## 3. Data Flow Diagram
*(to be added)*

## 4. Use Case Diagram
*(to be added)*

## 5. Class Diagram
*(to be added)*

## 6. Data Model
*(to be added)*

## 7. Interface Design Description
*(to be added)*
