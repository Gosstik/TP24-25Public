//
// Created by akhtyamovpavel on 5/1/20.
//


#pragma once

#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>

using FSPath = std::filesystem::path;

class TreeTestCase : public ::testing::Test { // NOLINT
protected:
  FSPath test_dir_ = std::filesystem::temp_directory_path() / "tree_test_dir";
  FSPath file1_ = test_dir_ / "file1";
  FSPath inner_dir_ = test_dir_ / "inner_dir";

  void SetUp() override {
    std::filesystem::create_directory(test_dir_);
    std::filesystem::create_directory(inner_dir_);

    {
      std::ofstream ofs1(file1_);
      ofs1 << "create";
      ofs1.close();
    }
  }

  void TearDown() override { std::filesystem::remove_all(test_dir_); }
};


