#include <gtest/gtest.h>
#include <magnetar/magnetar.h>

using namespace magnetar;
class MemoryFileSystemTestFixture: public testing::Test
{
public:
    static constexpr const char* text_file_path = "/etc/text-file.txt";


    void SetUp() override
    {
        fs = create_reference<MemoryFileSystem>();
        fs->set_file(text_file_path, "hello world");
    }

    void TearDown() override
    {

    }

    Ref<MemoryFileSystem> fs;

};

TEST_F(MemoryFileSystemTestFixture, OpensAFile)
{
    auto file = fs->open(text_file_path, FileMode::READ);
    auto data = file->read_all();
    data.push_back('\0');
    std::string str = (const char*)&data[0];
    EXPECT_TRUE(file != nullptr);
    EXPECT_EQ(str, "hello world");
}   