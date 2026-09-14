Hotel Room Booking System — Group 02

Overview

This is a simple Tkinter-based Hotel Room Booking prototype implementing features from the provided requirements specification: account registration/login, room search/listing, bookings with date checks, services, transactions (simulated), booking lifecycle (reserve/confirm/check-in/check-out/cancel), basic reports, and admin/staff management screens.

Run

From the project root run:

```powershell
python src/main.py
```

Default admin account:
- username: admin
- password: 123456

Notes

- The app uses SQLite database `hotel.db` in the project root. Database schema is created/updated automatically on first run via `database.init_db()`.
- Passwords are stored as SHA-256 hashes.
- Payment and refunds are simulated.

Quick git commit (optional)

If you want to commit the changes locally (assuming this folder is a git repo):

```powershell
git add .
git commit -m "Implement features: booking lifecycle, services, payments, admin UI"
```

Next steps you may ask me to do:
- Add UI to attach services during booking flow for customers.
- Add automated tests for `database.py` functions.
- Improve validation, error handling, and localization.
