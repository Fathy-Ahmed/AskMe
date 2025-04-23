# AskMe Console App (C++ OOP Project)

A file-based console application that simulates the core features of an AskMe-style platform. Designed using Object-Oriented Programming (OOP) principles in C++.

## 🚀 Features

- 🔐 **Login / Signup / Sign Out**
  - Users can create accounts with name, email, username, and password
  - Support for anonymous questions

- 💬 **Questions & Answers**
  - Ask questions to other users
  - Answer questions directed to you
  - View:
    - Questions you received
    - Questions you asked
    - All feed questions (involving you)

- 🔁 **Threaded Questions**
  - Questions can have follow-up threads
  - Removing a parent question deletes the full thread

- 🗑️ **Safe Delete**
  - You can only delete your own questions

## 🧠 Design Highlights

- Each user and question has a system-generated unique ID
- Questions are stored in threads (parent–child relationship)
- File-based system that saves and loads state on every run
- Supports multiple users in parallel (e.g., if multiple terminals are open)

## 📁 Technologies Used

- C++ (OOP)
- File I/O (text files)
- Console-based interface

## 📌 How to Run

1. Clone the repo
2. Open the project in Visual Studio
3. Build and run

```bash
git clone https://github.com/your-username/AskMe.git
