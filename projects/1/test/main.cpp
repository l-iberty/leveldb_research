#include <iostream>
#include <leveldb/db.h>

void test1()
{
    leveldb::DB *db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, "./testdb", &db);
    assert(status.ok());

    std::string key;
    std::string value;
    int nums[] = {2, 1, 4, 5, 9, 0, 3};

    for (int i : nums)
    {
        key = "key" + std::to_string(i);
        value = key + "@value";
        status = db->Put(leveldb::WriteOptions(), key, value);
        assert(status.ok());
    }

    leveldb::Iterator *it = db->NewIterator(leveldb::ReadOptions());
    it->SeekToFirst();
    while (it->Valid())
    {
        std::string k = it->key().ToString();
        std::string v = it->value().ToString();
        std::cout << "<" << k << ", " << v << ">" << std::endl;
        it->Next();
    }

    delete it;
    delete db;
}

int main()
{
#if 0
    test1();
#else
    leveldb::DB *db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, "./testdb", &db);
    std::string value;

    status = db->Get(leveldb::ReadOptions(), "Bob", &value);
    if (!status.ok())
    {
        std::cout << "key \"Bob\" not found." << std::endl;
    }
    else
    {
        std::cout << "key \"Bob\" found" << std::endl;
    }

    status = db->Put(leveldb::WriteOptions(), "Alice", "Alice@alice.com");
    assert(status.ok());

    status = db->Get(leveldb::ReadOptions(), "Alice", &value);
    assert(status.ok());
    printf("<Alice,%s>\n", value.c_str());

    status = db->Put(leveldb::WriteOptions(), "Bob", "Bob@bob.com");

    status = db->Get(leveldb::ReadOptions(), "Bob", &value);
    assert(status.ok());
    printf("<Bob,%s>\n", value.c_str());

    status = db->Delete(leveldb::WriteOptions(), "Alice");
    assert(status.ok());

    status = db->Get(leveldb::ReadOptions(), "Alice", &value);
    if (!status.ok())
    {
        std::cout << "key \"Alice\" deleted successfully." << std::endl;
    }
    else
    {
        std::cout << "failed to delete key \"Alice\"." << std::endl;
    }

    status = db->Get(leveldb::ReadOptions(), "apple", &value);
    if (!status.ok())
    {
        std::cout << "key \"apple\" not found." << std::endl;
    }
    else
    {
        std::cout << "key \"apple\" found" << std::endl;
    }
    delete db;
    return 0;
#endif
}