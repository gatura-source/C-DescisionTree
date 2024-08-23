import csv

# Define the data for the CSV file
data = [
    ["Name", "Age", "Email"],   # Header
    ["Alice", "30", "alice@example.com"],
    ["Bob", "", "bob@example.com"],   # Missing Age
    ["Ann", "25", ""],      # Missing Email
    ["David", "40", "david@example.com"],
    ["Eve", "", ""],            # Missing Age and Email
]

# Specify the file name
filename = "sample_with_missing_values.csv"

# Write the data to the CSV file
with open(filename, mode="w", newline="") as file:
    writer = csv.writer(file)
    writer.writerows(data)

print(f"CSV file '{filename}' has been created.")
