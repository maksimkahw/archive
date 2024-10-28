from threading import Thread, Lock
import random

def fileWriter(filename: str, line: str, count: int):
    with open(filename, "wb+") as file:
        file.write(line.encode() * count)

def generateString(thread_id: int, result_list: list, lock: Lock):
    string: str = ''
    for i in range(1, 5_000_001):
        # string += chr(random.randint(32, 126))  # Генерация только печатаемых символов # Используем Lock для обеспечения потокобезопасности при записи в список
        string += chr(random.randint(32, 50))
    with lock:
        result_list[thread_id] = string  # Сохраняем строку в списке по индексу потока
    print(f"Thread {thread_id} finished.")

# Создание списка для хранения результатов
results = [None] * 3  # Инициализируем список с 3 элементами
lock = Lock()  # Создаем объект Lock
threads = []

# Создание и запуск потоков
for i in range(3):
    print("start thread", i)
    thread = Thread(target=generateString, args=(i, results, lock))
    threads.append(thread)
    thread.start()

# Ожидание завершения всех потоков
for thread in threads:
    thread.join()

# Теперь results содержит сгенерированные строки
for i, result in enumerate(results):
    print(f"Result from thread {i}: {len(result)} characters")

for index, string in enumerate(results):
    fileWriter(f"file{index+1}.txt", results[index], 2)
    print(f"File {index+1} writed")

print("Ready")