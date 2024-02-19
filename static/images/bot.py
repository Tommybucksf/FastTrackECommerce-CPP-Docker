import os

# Шлях до директорії з зображеннями
directory = '/Users/mandalorian/Dev/X/static/images'

# Список нових імен файлів
new_names = [
    "dell_inspiron_15.jpg",
    "hp_pavilion_14.jpg",
    "lenovo_ideapad_3.jpg",
    "macbook_air.jpg",
    "asus_zenbook_14.jpg",
    "acer_swift_3.jpg",
    "surface_laptop_4.jpg",
    "dell_xps_13.jpg",
    "hp_spectre_x360.jpg",
    "lenovo_legion_5.jpg"
]

# Отримуємо список усіх файлів у директорії з розширенням .jpg
files = [f for f in os.listdir(directory) if os.path.isfile(os.path.join(directory, f)) and f.endswith('.jpg')]

# Переконуємося, що кількість файлів відповідає кількості нових імен
if len(files) != len(new_names):
    print(f"Помилка: кількість файлів ({len(files)}) не відповідає кількості нових імен ({len(new_names)}).")
else:
    # Перейменовуємо файли
    for old_name, new_name in zip(files, new_names):
        os.rename(os.path.join(directory, old_name), os.path.join(directory, new_name))
    print("Усі файли успішно перейменовано.")
