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
    test1();
#if 0
    leveldb::DB *db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, "./testdb", &db);
    std::string value;

    std::string key1 = "Alice";
    std::string value1 = "Alice@alice.com";
    status = db->Put(leveldb::WriteOptions(), key1, value1);
    assert(status.ok());

    status = db->Get(leveldb::ReadOptions(), key1, &value);
    assert(status.ok());
    printf("<%s,%s>\n", key1.c_str(), value.c_str());

    std::string key2 = "Bob";
    std::string value2 = "Bob@bob.com";
    status = db->Put(leveldb::WriteOptions(), key2, value2);

    status = db->Get(leveldb::ReadOptions(), key2, &value);
    assert(status.ok());
    printf("<%s,%s>\n", key2.c_str(), value.c_str());

    status = db->Put(leveldb::WriteOptions(), key1, value2);
    status = db->Get(leveldb::ReadOptions(), key1, &value);
    assert(status.ok());
    printf("<%s,%s>\n", key1.c_str(), value.c_str());

    status = db->Delete(leveldb::WriteOptions(), key1);
    assert(status.ok());

    status = db->Get(leveldb::ReadOptions(), key1, &value);
    if (!status.ok())
    {
        std::cout << "key " << key1 << " deleted successfully." << std::endl;
    } else
    {
        std::cout << "failed to delete key " << key1 << std::endl;
    }

    delete db;
    return 0;
#endif
}