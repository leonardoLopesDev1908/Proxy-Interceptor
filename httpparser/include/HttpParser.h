#ifndef HTTP_SERVER4_REQUEST_PARSER_H
#define HTTP_SERVER4_REQUEST_PARSER_H

/* RFC 9112 HTTP/1.1 https://datatracker.ietf.org/doc/html/rfc9112
* 
* The normal procedure for parsing an HTTP message is 
*		- to read the start - line into a structure, 
*		- read each header field line into a hash table by 
*		  field name until the empty line, 
*		- and then use the parsed data to determine if a 
*		  message body is expected.
* If a message body has been indicated,
* then it is read as a stream until an amount of
* octets equal to the message body length is read 
* or the connection is closed.
*/

class HttpParser
{
    //
// request_parser.hpp
// ~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2025 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//


#include <tuple>

    namespace http {
        namespace server4 {

            struct request;

            /// Parser for incoming requests.
            class request_parser
            {
            public:
                /// Construct ready to parse the request method.
                request_parser();

                /// Reset to initial parser state.
                void reset();

                /// Result of parse.
                enum result_type { good, bad, indeterminate };

                /// Parse some data. The enum return value is good when a complete request has
                /// been parsed, bad if the data is invalid, indeterminate when more data is
                /// required. The InputIterator return value indicates how much of the input
                /// has been consumed.
                template <typename InputIterator>
                std::tuple<result_type, InputIterator> parse(request& req,
                    InputIterator begin, InputIterator end)
                {
                    while (begin != end)
                    {
                        result_type result = consume(req, *begin++);
                        if (result == good || result == bad)
                            return std::make_tuple(result, begin);
                    }
                    return std::make_tuple(indeterminate, begin);
                }

            private:
                /// Handle the next character of input.
                result_type consume(request& req, char input);

                /// Check if a byte is an HTTP character.
                static bool is_char(int c);

                /// Check if a byte is an HTTP control character.
                static bool is_ctl(int c);

                /// Check if a byte is defined as an HTTP tspecial character.
                static bool is_tspecial(int c);

                /// Check if a byte is a digit.
                static bool is_digit(int c);

                /// The current state of the parser.
                enum state
                {
                    method_start,
                    method,
                    uri,
                    http_version_h,
                    http_version_t_1,
                    http_version_t_2,
                    http_version_p,
                    http_version_slash,
                    http_version_major_start,
                    http_version_major,
                    http_version_minor_start,
                    http_version_minor,
                    expecting_newline_1,
                    header_line_start,
                    header_lws,
                    header_name,
                    space_before_header_value,
                    header_value,
                    expecting_newline_2,
                    expecting_newline_3
                } state_;
            };

        } // namespace server4
    } // namespace http

};

#endif 