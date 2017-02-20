# VK (QML)
Библиотека для работы с соц.сатью "ВКонтакте", внутри QT(QML) приложения.

#### Возможности

1. Авторизация/уатентификация пользователя
2. Получение почты пользователя
3. Получения имени пользователя
4. Получение текущей аватарки пользователя со страницы
5. Получение списка друзей пользователя
6. Отправка сообщений друзьям

#### Установка

1. Скачиваем исходники
2. Открываем их в Qt
3. Собираем (просто жмём  кнопку с молотком)
4. Идем в папку c релиз версией собранной библиотеки и копируем от туда файл libvk.a в папку lib (допустим lib создана на рабочем столе)
5. Идем в исходники библиотеки и копируем заголовочный файл vk.h в туже папку lib
6. Создаете свой проект или если есть уже рабочий, то копируете туда папку lib (да... мы не ищем легких путей)
7. В файле вашего проекта myproject.pro, на пустом месте жмем правой кнопкой мыши и выбираем add library
8. В появившемся окне выбираем External library и жмем далее
9. Указываем путь до библиотеки, путь подключения и свою платформу
10. В файле проекта main.cpp делаем подключение библиотеки #include "lib/vk.h" и пишем код
```c++
   QString appVk = "123123123"; // id вашего приложения полученное при регистрации в ВК
   Vk vk(appVk);
   context->setContextProperty(QStringLiteral("vk"), &vk);
```
#### Использование

В QML создаем WebView примерно следующего содержания

  ```php
   WebView {
    anchors.fill: parent
    url: m_url

    onUrlChanged: {
        vk.listening = url;
    }
}
```   
В main.qml можно добавить такие переменные и работать с ними уже в самом QML

  ```php
    property var m_url: vk.url

    property var photo: vk.photo
    property var token: vk.token
    property var mail: vk.mail
    property var name: vk.name
    property var id: vk.id

    property var frendsPhoto: vk.frendsPhoto
    property var frendsName: vk.frendsName
    property var frendsId: vk.frendsId
```   

#### Методы
```php
Обязательные методы
    vk.url - добавить в WebView.url
    vk.listening - добавить в WebView.onUrlChanged

Методы для пользователя
    vk.photo
    vk.token
    vk.mail
    vk.name
    vk.id

Друзья пользователя
    vk.frendsPhoto
    vk.frendsName
    vk.frendsId
```  
