#include <gtest/gtest.h>

#include "manager.hpp"

class FileTest : public testing::Test {
    protected:
        FileService* service;

        FileTest()
        {
            GMManager::get_instance()->start_file_service();
            service = GMManager::get_instance()->get_file_service();
        }

        void SetUp() override
        {
        }

        void TearDown() override
        {
            service->close_all();
        }
};

TEST_F(FileTest, read_from_working_dir)
{
    std::string working_dir = service->get_working_dir();
    GMFile file = service->open_file(working_dir + "/LICENSE", GMFileType::TEXT, GMFileMode::READ);
    ASSERT_EQ(service->n_files_opened(), 1);
    std::string line = file.read_line();
    ASSERT_EQ(line, "MIT License");
}

TEST_F(FileTest, write_home_dir_then_read)
{
    std::string path = service->get_home_dir() + "/passoca.txt";
    GMFile file = service->open_file(path, GMFileType::TEXT, GMFileMode::WRITE);
    file.write_line("Lorem Ipsum");
    service->close_file(path);
    ASSERT_EQ(service->n_files_opened(), 0);

    file = service->open_file(path, GMFileType::TEXT, GMFileMode::READ);
    ASSERT_EQ(service->n_files_opened(), 1);
    std::string line = file.read_line();
    ASSERT_EQ(line, "Lorem Ipsum");
}

TEST_F(FileTest, get_file_paths_from_dir_test)
{
    std::vector<std::string> paths = service->get_file_paths_from_dir("src/test/assets");
    ASSERT_EQ(paths.size(), 3);
    ASSERT_TRUE(std::find(paths.begin(), paths.end(), "src/test/assets/sample.csv") != paths.end());
    ASSERT_TRUE(std::find(paths.begin(), paths.end(), "src/test/assets/sample.png") != paths.end());
    ASSERT_TRUE(std::find(paths.begin(), paths.end(), "src/test/assets/sample.xml") != paths.end());
}

TEST_F(FileTest, seek_and_write_then_reload_and_read)
{
    GMFile file = service->open_file("test.gma", GMFileType::BINARY, GMFileMode::WRITE);
    for (int i = 0; i<100; ++i)
        file.write_byte(0);
    file.seek(50);
    file.write_padded_string("PASSOCA", 0, 10);
    ASSERT_EQ(file.get_size(), 100);
    service->close_file("test.gma");
    file = service->open_file("test.gma", GMFileType::BINARY, GMFileMode::READ);
    file.seek(50);
    ASSERT_EQ(file.read_byte(), 'P');
    ASSERT_EQ(file.read_byte(), 'A');
    ASSERT_EQ(file.read_byte(), 'S');
    ASSERT_EQ(file.read_byte(), 'S');
    ASSERT_EQ(file.get_size(), 100);
}