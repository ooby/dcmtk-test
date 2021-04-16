## Пример загрузки DICOM-файла и последующей ее обработки

## Что надо:
- Linux: Ubuntu/Debian
- OpenCV
- DCMTK

## Установка OpenCV пошагово:
1. Ставим необходимые пакеты:
```bash
sudo apt update && sudo apt install -y git cmake build-essential wget unzip
```
2. Создаем временную папку для OpenCV и переходим в нее:
```bash
mkdir -p opencv && cd opencv
```
3. Скачиваем и разархивируем OpenCV:
```bash
wget -O opencv.zip https://github.com/opencv/opencv/archive/master.zip
unzip opencv.zip
```
4. Создаем папку для сборки и переходим в нее:
```bash
mkdir -p build && cd build
```
5. Подготавливаем файлы для сборки:
```bash
cmake  ../opencv-master
```
6. Производим сборку файлов OpenCV:
```bash
make -j4
# здесь -j4 означает что сборка происходит в 4 параллельных потока
# например, можно производить сборку в 8 потоков с флагом -j8, если позволяют мощности процессора
# сборка будет долгая...
```
7. Устанавливаем файлы OpenCV в систему, по-умолчанию ставятся в папку `/usr/local/`
```bash
sudo make install
# нужны соответствующие права
```
8. Выходим из папки, чистим все:
```bash
cd ../..
rm -rf opencv
```

## Установка DCMTK пошагово:
1. Клонируем репу из github.com и переходим в нее:
```bash
git clone https://github.com/DCMTK/dcmtk.git
cd dcmtk
```
4. Создаем папку для сборки и переходим в нее:
```bash
mkdir -p build && cd build
```
5. Подготавливаем файлы для сборки:
```bash
cmake  ..
```
6. Производим сборку файлов DCMTK:
```bash
make -j4
```
8. Устанавливаем файлы DCMTK в систему, по-умолчанию ставятся в папку `/usr/local/`
```bash
sudo make DESTDIR=/usr/local install
# нужны соответствующие права
# здесь надо быть внимательным и понимать куда и что кладем
```
9. Выходим из папки, чистим все:
```bash
cd ../..
rm -rf dcmtk
```

## Программа `test`
1. Клонируем репу из github.com и переходим в нее:
```bash
git clone https://github.com/ooby/dcmtk-test.git
cd dcmtk-test
```
2. Подготавливаем файлы для сборки:
```bash
cmake .
```
3. Производим сборку:
```bash
make
```
4. В результате сборки (если всё было сделано правильно) появится исполняемый файл `test`, который можно исполнить следующим образом:
```bash
./test
```
5. Результат исполнения программы сохранится в том же каталоге в виде файла `test.png`