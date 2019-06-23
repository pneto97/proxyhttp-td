#include "cache.hpp"

Cache::Cache(/* args */)
{
}

Cache::~Cache()
{
}

Response Cache::getFromCache(Request req) {
    std::vector<char> request;
    Response resp;
    std::string fileName;

    fileName = req.getHost() + req.getFileRequestSemBarra();

    std::ifstream requestFile ("../cache/" + fileName, std::ios::binary);

    if( requestFile.is_open() ){
        try
        {
            requestFile.unsetf(std::ios::skipws);
            const auto begin = requestFile.tellg();
            requestFile.seekg (0, std::ios::end);
            requestFile.seekg(0, std::ios::beg);

            const auto end = requestFile.tellg();
            request.reserve(end-begin);
            request.insert(request.begin(), std::istream_iterator<char>(requestFile), std::istream_iterator<char>());
        }
        catch(const std::exception& e)
        {
            std::cerr << "Tentou ler arquivo que nao existe: " + fileName << std::endl;
        }
    } else {
        std::cerr << "Erro ao tentar abrir arquivo " + fileName << std::endl;
        return resp;
    }
    requestFile.close();

    resp.createResponse(request, -1);

    return resp;
}

VALOR_RETORNO Cache::lancarNaCache(Response resp, Request req) {
    if (resp.getResponseCode() != "200")
    {
        return VALOR_RETORNO::SUCCES_ON_EXECUTION;
    }
    
    std::string fileName = "../cache/" + req.getHost() + req.getFileRequestSemBarra();

    std::ofstream cacheFile (fileName.c_str(), std::ios::out | std::ios::binary);
    if (cacheFile.is_open())
    {
        cacheFile.write((const char *)&resp.getBinaryResponse()[0], resp.getBinaryResponse().size());
        cacheFile.close();
        return VALOR_RETORNO::SUCCES_ON_EXECUTION;
    } else {
        return VALOR_RETORNO::ERROR;
    }
}
