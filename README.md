# JSON library install
Для 28-ї задачі треба зробити введення/виведення в форматі JSON, для чого знадобиться бібліотека nlohmann/json.hpp Знайти її можна за посиланням: https://github.com/nlohmann/json/releases/tag/v3.10.4 , де знадобиться include.zip. Файли include, single_include, meson_build розархівувати в директорії проекту. В Visual Studio 2019 включити бібліотеку можна за наступним алгоритмом: Проект(пкм) -> Свойства -> С/С++ -> Дополнительные каталоги включаемых файлов -> вибрати папку include (вище розархівована).

Включити бібліотеку #include <nlohmann/json.hpp>
