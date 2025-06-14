#ifndef CLIENT_HTTP_HPP
#define CLIENT_HTTP_HPP

/**
 * \file client_http.hpp
 * \brief Заголовочный файл с функциями HTTP-клиента для взаимодействия с сервером.
 *
 * В этом файле объявлены функции:
 * - file_name: формирование имени файла-словаря по длине слова;
 * - make_request: создание HTTP-запроса к серверу с указанием host и версии;
 * - request_to_server: отправка HTTP-запроса и получение строки ответа.
 */

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <iostream>
#include <string>
#include <stdexcept>

namespace beast = boost::beast;     /**< Пространство имён Boost.Beast. */
namespace http  = beast::http;       /**< Пространство имён для HTTP из Beast. */
namespace net   = boost::asio;       /**< Пространство имён Boost.Asio. */
using tcp       = net::ip::tcp;      /**< Тип TCP-сокета из Boost.Asio. */

/**
 * \brief Формирует имя файла-словаря по длине слова.
 * \param len_w Длина проверяемого слова.
 * \return std::string Имя файла-словаря (например, "dict_5.txt").
 * \throw std::runtime_error Если len_w не равна 4, 5, 6.
 */
std::string file_name(int len_w);

/**
 * \brief Создаёт HTTP-запрос к серверу.
 * \param mode    Режим запроса: "check_word" для проверки или "get_word" для получения слова.
 * \param len_w   Длина слова.
 * \param word    Слово для проверки (mode == "check_word") или пустая строка (mode == "get_word").
 * \param host    Адрес HTTP-сервера (например, "localhost").
 * \param version Версия HTTP (например, 11 для HTTP/1.1).
 * \return http::request<http::string_body> Сформированный HTTP-запрос.
 * \throw http::runtime_error Если введен не верный параметр mode(не "get_word" и "check_word")
 */
http::request<http::string_body> make_request(std::string const& mode,
                                              int len_w,
                                              std::string const& word,
                                              std::string const& host,
                                              int version);

/**
 * \brief Отправляет HTTP-запрос на сервер и возвращает текст ответа.
 * \param mode   Режим запроса: "check_word" или "get_word".
 * \param len_w  Длина слова.
 * \param word   Слово для отправки.
 * \return std::string Тело ответа, полученное от сервера.
 */
std::string request_to_server(std::string mode, int len_w, std::string word);

#endif // CLIENT_HTTP_HPP
