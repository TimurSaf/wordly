#ifndef HTTP_SERVER_HPP
#define HTTP_SERVER_HPP

/**
 * \file
 * \brief Заголовочный файл с объявлениями функций HTTP-сервера и утилит для работы со словарями.
 *
 * Содержит прототипы функций для получения случайного слова, проверки слова в словаре,
 * формирования имени файла-словаря, обработки HTTP-запросов и управления сессиями сервера.
 */

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/config.hpp>
#include <cstdlib>
#include <memory>
#include <thread>
#include <stdlib.h>

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <unordered_set>
#include <stdexcept>

namespace beast = boost::beast;     /**< Пространство имён Boost.Beast. */
namespace http  = beast::http;       /**< Пространство имён для HTTP из Beast. */
namespace net   = boost::asio;       /**< Пространство имён Boost.Asio. */
using tcp       = net::ip::tcp;      /**< Тип TCP-сокета из Boost.Asio. */

/**
 * \brief Получает случайное слово заданной длины из файла-словaря.
 * \param len_w Длина слова.
 * \return std::string Случайное слово длины len_w.'
 * \throw std::runtime_error Если len_w не равна 4, 5, 6.
 */
std::string get_word(int len_w);

/**
 * \brief Проверяет существование слова в словаре.
 * \param word Ссылка на строку со словом для проверки.
 * \return std::string "correct word", если слово найдено; иначе "not exist".
 * \throw std::runtime_error Если длина word не равна 4, 5, 6.
 */
std::string check_word(std::string& word);

/**
 * \brief Формирует имя файла-словaря по длине слова.
 * \param len_w Длина слова.
 * \return std::string Имя файла-словaря (например, "dict_5.txt").
 * \throw std::runtime_error Если len_w не равна 4, 5, 6.
 */
std::string file_name(int len_w);

/**
 * \brief Обрабатывает HTTP-запрос и формирует ответ.
 * \tparam Body      Тип тела запроса.
 * \tparam Allocator Тип аллокатора для полей HTTP.
 * \param doc_root   Путь к корню документов (string_view).
 * \param req        Перемещаемый HTTP-запрос.
 * \return http::message_generator Генератор HTTP-ответа.
 */
template <class Body, class Allocator>
http::message_generator handle_request(
    beast::string_view doc_root,
    http::request<Body, http::basic_fields<Allocator>>&& req);

/**
 * \brief Обрабатывает сессию TCP-соединения с клиентом.
 * \param socket   Сокет, по которому установлено соединение.
 * \param doc_root Указатель на строку с корнем документов.
 * \return void
 */
void do_session(
    tcp::socket& socket,
    std::string const& doc_root);

#endif // HTTP_SERVER_HPP
