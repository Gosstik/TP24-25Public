//
// Created by akhtyamovpavel on 5/1/20.
//

#include "TreeTestCase.h"

#include <stdexcept>
#include <unordered_set>

#include <Tree.h>

TEST_F(TreeTestCase, GetTreeAllFiles) {
  std::unordered_set<std::string> file_node_set = {
      file1_.filename().string(),
      inner_dir_.filename().string(),
  };

  auto res = GetTree(test_dir_.string(), false);

  EXPECT_EQ(res.name, test_dir_.filename().string());
  EXPECT_TRUE(res.is_dir);

  EXPECT_EQ(res.children.size(), 2);
  for (auto &file : res.children) {
    EXPECT_TRUE(file_node_set.count(file.name) == 1);
  }
}
