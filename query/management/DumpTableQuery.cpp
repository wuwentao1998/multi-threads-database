//
// Created by liu on 18-10-25.
//

#include "DumpTableQuery.h"
#include "../../db/Database.h"

#include <fstream>

constexpr const char *DumpTableQuery::qname;

QueryResult::Ptr DumpTableQuery::execute() {
    using namespace std;
    auto &db = Database::getInstance();
    try {
        ofstream outfile(this->fileName);
        if (!outfile.is_open()) {
            return make_unique<ErrorMsgResult>(qname, "Cannot open file '?'"_f % this->fileName);
        }
        outfile << db[this->targetTable];
        outfile.close();
        return make_unique<SuccessMsgResult>(qname, targetTable);
    } catch (const exception &e) {
        return make_unique<ErrorMsgResult>(qname, e.what());
    }
}

std::string DumpTableQuery::toString() {
    return "QUERY = Dump TABLE \"" + this->targetTable + "\", FILE = \"" + this->fileName + "\"";
}
