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

### Context Diagram (Level 0)
External entities interacting with the system:
- **Guest** → sends booking requests → System → returns booking confirmations
- **Receptionist** → sends check-in/check-out actions → System → returns room status
- **Admin** → receives reports → System

### Level 1 DFD

**Processes:**
- **1.0 Booking** – receives requests from Guest, checks/updates `D1 - Room`, creates a record in `D2 - Booking`
- **2.0 Payment** – reads `D2 - Booking`, records transaction in `D3 - Payment`
- **3.0 Check-in / Check-out** – reads `D2 - Booking`, updates `D1 - Room` status, interacts with Receptionist

**Data stores:**
- **D1 - Room**: room info, type, price, status
- **D2 - Booking**: booking records, dates, guest info
- **D3 - Payment**: transaction records, amount, method

## 4. Use Case Diagram

**Actors:** Guest, Receptionist, Admin

**Use cases:**
| Actor | Use cases |
|---|---|
| Guest | Search rooms, Book a room, Make payment, Manage booking (view/edit/cancel) |
| Receptionist | Check-in / Check-out, Manage booking (walk-in) |
| Admin | Manage rooms, View reports |

**Relationships:**
- Guest → Search rooms, Book a room, Make payment, Manage booking
- Receptionist → Check-in/out, Manage booking
- Admin → Manage rooms, View reports
- "Book a room" includes "Make payment" (extend/include relationship, optional to model explicitly)

## 5. Class Diagram

**Classes:**
- **Guest**: id, name, email, phone — register(), login(), searchRooms()
- **Booking**: id, checkInDate, checkOutDate, status — createBooking(), cancelBooking()
- **Room**: id, number, status — updateStatus()
- **RoomType**: id, name, price, capacity
- **Payment**: id, amount, method, status — processPayment()
- **Staff**: id, name, role — checkIn(), checkOut()

**Relationships:**
- Guest (1) → Booking (many): a guest makes multiple bookings
- Booking (many) → Room (1): each booking reserves one room
- Room (many) → RoomType (1): each room belongs to one room type
- Booking (1) → Payment (1): each booking has one payment
- Staff (1) → Booking (many): staff manage multiple bookings (check-in/out)

## 6. Data Model
*(to be added)*

## 7. Interface Design Description

### Screen: Room Search & Booking (Guest)
- **Search bar**: check-in date, check-out date, number of guests, "Search" button
- **Results list**: room cards showing room type, capacity, price/night, and a "Select" button
- Selecting a room leads to booking confirmation, then payment

### Screen: Room Details
- Photos, amenities, price, capacity, availability calendar, "Book now" button

### Screen: My Bookings (Guest)
- List of current/past bookings with status, dates, and options to view/edit/cancel

### Screen: Reception Dashboard (Receptionist)
- Table of today's bookings with check-in/check-out actions and room status controls

### Screen: Admin Dashboard
- Room management (CRUD), staff management, revenue/occupancy reports, promotions

*(Note: if implemented as a console application, describe each screen above as text-based menus/prompts instead.)*
