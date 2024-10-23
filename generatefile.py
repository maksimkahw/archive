
def fileWriter(filename: str, line: str, count: int):
    with open(filename, "wb+") as file:
        file.write(line.encode() * count)

string = "hello!\n"
string2 = "privet!\n"
string3 = "aboba\n"

fileWriter("file1.txt", string, 1000)
fileWriter("file2.txt", string2, 1000)
fileWriter("file3.txt", string3, 100)