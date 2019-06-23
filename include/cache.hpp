#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <iostream>

#include "Response.hpp"
#include "Request.hpp"

class Cache
{
private:
    /* data */
public:
    Cache(/* args */);
    ~Cache();
    // Lê do arquivo binario e retorna uma reposta com o conteudo do arquivo
    Response getFromCache(Request fileName);
    VALOR_RETORNO lancarNaCache(Response resp, Request req);
};