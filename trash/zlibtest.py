import zlib

# Функция для сжатия файла
def compress_file(input_file_path, output_file_path):
    # Открываем входной файл для чтения в бинарном режиме 
    with open(input_file_path, 'rb') as input_file:
        # Читаем данные побайтово
        data = input_file.read()
        
        # Сжимаем данные
        compressed_data = zlib.compress(data)
        
        # Открываем выходной файл для записи сжатых данных
        with open(output_file_path, 'wb') as output_file:
            output_file.write(compressed_data)
    
    print(f"Файл '{input_file_path}' успешно сжат и сохранен как '{output_file_path}'.")

# Функция для распаковки файла
def decompress_file(input_file_path, output_file_path):
    # Открываем входной файл для чтения в бинарном режиме
    with open(input_file_path, 'rb') as input_file:
        # Читаем сжатые данные
        compressed_data = input_file.read()
        
        # Распаковываем данные
        decompressed_data = zlib.decompress(compressed_data)
        
        # Открываем выходной файл для записи распакованных данных
        with open(output_file_path, 'wb') as output_file:
            output_file.write(decompressed_data)
    print(f"Файл '{input_file_path}' успешно распакован и сохранен как '{output_file_path}'.")

# Пример использования
input_file = 'file3.txt'  # Укажите путь к вашему входному файлу
compressed_file = 'example.zlib'  # Путь для сохранения сжатого файла
decompressed_file = 'decompressed_example.txt'  # Путь для сохранения распакованного файла

# Сжимаем файл
for i in range(3):
    compress_file(f"file{i+1}.txt", f"example{i+1}.txt")

# Распаковываем файл
# decompress_file(compressed_file, decompressed_file)