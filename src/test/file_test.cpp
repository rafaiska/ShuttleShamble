#include <gtest/gtest.h>

#include "manager.hpp"

class FileTest : public testing::Test {
    protected:
        FileService* service;

        FileTest()
        {
            GMManager::get_instance()->start_test_services();
            service = GMManager::get_instance()->get_file_service();
        }

        void SetUp() override
        {
        }

        void TearDown() override
        {
        }
};

TEST_F(FileTest, read_from_working_dir)
{
    std::string working_dir = service->get_working_dir();
    GMFile& file = service->open_file(working_dir + "/LICENSE", GMFileType::TEXT, GMFileMode::READ);
    ASSERT_EQ(service->n_files_opened(), 1);
    std::string line = file.read_line();
    ASSERT_EQ(line, "MIT License");
}

TEST_F(FileTest, write_home_dir_then_read)
{
    std::string path = service->get_home_dir() + "/passoca.txt";
    GMFile& file = service->open_file(path, GMFileType::TEXT, GMFileMode::WRITE);
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