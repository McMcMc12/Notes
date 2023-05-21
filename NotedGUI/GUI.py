import tkinter as tk
from tkinter import messagebox

# Read the contents of the reminder.txt file
with open(r"C:\Users\mcron\OneDrive\Desktop\reminders.txt", 'r') as file:
    reminder_contents = file.read()

# Create a floating window
window = tk.Tk()
window.title('Reminder')
window.geometry('400x300')  # Set the window size as desired

# Display the reminder contents
label = tk.Label(window, text=reminder_contents, wraplength=380)
label.pack(pady=20)

# Run the application
window.mainloop()