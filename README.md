# 🏫 University Room Management System

A C++ console application that helps manage university buildings, classrooms, lab rooms, class schedules, and room bookings, with data stored in plain text files.

![Language](https://img.shields.io/badge/language-C%2B%2B-blue)
![Type](https://img.shields.io/badge/type-Console%20App-lightgrey)
![Status](https://img.shields.io/badge/status-In%20Development-yellow)

---

## 📌 Features

- 🏢 **Building information**: view full details of every building
- 🏫 **Classroom & lab room lists**: browse all classrooms and labs
- 🗓️ **Room schedules**: class schedules for each room
- ✅ **Room booking**: book an available room
- ❌ **Booking cancellation**: cancel an existing booking
- 📄 **File-based storage**: data is kept in text files, so no database is needed

---

## 📂 Project Structure
University_Room_Management_System/
│
├── Buildingsinfo/ # Building data files
├── Classroomsinfo/ # Classroom data files
├── Labroomsinfo/ # Lab room data files
├── RoomSchedules/ # Schedule files for each room
│
├── Main.cpp # ▶ Entry point (run this file)
├── Building_rooms_time_scedule.cpp
├── Full_Building_show.cpp
├── Room_Booking_System.cpp
│
├── test*.cpp / test01A.txt # Test files used during development
└── README.md

---

## 🛠️ Requirements

- A C++ compiler (g++ / MinGW / MSVC)
- C++11 or later

---

## ▶️ How to Run

**1. Clone the repository**
```bash
git clone https://github.com/SaKin32/University_Room_Management_System.git
cd University_Room_Management_System
```

**2. Compile**
```bash
g++ Main.cpp -o main
```

**3. Run**
```bash
# Windows
main.exe

# Linux / macOS
./main
```

> ⚠️ Run the program from the project root folder so it can find the data folders (`Buildingsinfo`, `Classroomsinfo`, `Labroomsinfo`, `RoomSchedules`).

---

## 🧭 Usage

1. Run `Main.cpp`.
2. Choose an option from the menu.
3. View buildings, rooms, and schedules, or book/cancel a room.

<!-- Add a screenshot of your program here -->
<!-- ![Screenshot](screenshots/menu.png) -->

---

## 🚀 Future Improvements

- [ ] Input validation for booking time conflicts
- [ ] User login (admin / teacher / student)
- [ ] Search rooms by capacity or availability
- [ ] GUI or web version

---

## 👨‍💻 Author

**Md Showkotul Islam**
GitHub: [@SaKin32](https://github.com/SaKin32)

---

## 📄 License

This project is for educational purposes.
