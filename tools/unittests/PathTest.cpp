//===- PathTest.cpp -------------------------------------------------------===//
//
//                             The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#include "PathTest.h"
#include <bold/Support/Path.h>
#include <bold/Support/FileSystem.h>
#include <string>

using namespace bold;
using namespace bold::test;

//===----------------------------------------------------------------------===//
// PathTest
//===----------------------------------------------------------------------===//
// Constructor can do set-up work for all test here.
PathTest::PathTest()
{
  // create testee. modify it if need
  m_pTestee = new Path();
}

// Destructor can do clean-up work that doesn't throw exceptions here.
PathTest::~PathTest()
{
  delete m_pTestee;
}

// SetUp() will be called immediately before each test.
void PathTest::SetUp()
{
}

// TearDown() will be called immediately after each test.
void PathTest::TearDown()
{
}

//===----------------------------------------------------------------------===//
// Testcases
//===----------------------------------------------------------------------===//
PAT_C( PathTest, should_exist ) {
  std::string root(TOPDIR);
  root += "/tools/bold/unittests/PathTest.cpp";
  m_pTestee->assign(root);
  EXPECT_TRUE(exists(*m_pTestee));

  delete m_pTestee;
  m_pTestee = new Path(root);
  EXPECT_TRUE(exists(*m_pTestee));
}

PAT_C( PathTest, should_not_exist ) {
  const std::string root = "/luck";
  m_pTestee->assign(root);
  EXPECT_FALSE(exists(*m_pTestee));

  delete m_pTestee;
  m_pTestee = new Path(root);
  EXPECT_FALSE(exists(*m_pTestee));
}

PAT_C( PathTest, should_is_directory ) {
  const std::string root = "../././..";
  m_pTestee->assign(root);
  EXPECT_TRUE(exists(*m_pTestee));
  EXPECT_TRUE(is_directory(*m_pTestee));
  delete m_pTestee;
  m_pTestee = new Path(root);
  EXPECT_TRUE(exists(*m_pTestee));
  EXPECT_TRUE(is_directory(*m_pTestee));
}

PAT_C( PathTest, should_not_is_directory ) {
  const std::string root = "/luck";
  m_pTestee->assign(root);
  EXPECT_FALSE(exists(*m_pTestee));
  EXPECT_FALSE(is_directory(*m_pTestee));
  delete m_pTestee;
  m_pTestee = new Path(root);
  EXPECT_FALSE(exists(*m_pTestee));
  EXPECT_FALSE(is_directory(*m_pTestee));
}

PAT_C( PathTest, should_equal ) {
  const std::string root = "aaa/bbb/../../ccc/";
  m_pTestee->assign(root);

  Path* p2 = new Path("ccc///////");

  EXPECT_TRUE(*m_pTestee==*p2);

  delete m_pTestee;
  m_pTestee = new Path(root);
  EXPECT_TRUE(*m_pTestee==*m_pTestee);
  delete p2;
}

PAT_C( PathTest, should_not_equal ) {
  const std::string root = "aa/";
  Path* p2=new Path("aaa//");
//  p2->assign(root);
  m_pTestee->assign(root);
  EXPECT_TRUE(*m_pTestee!=*p2);

  delete m_pTestee;
  m_pTestee = new Path(root);
  EXPECT_TRUE(*m_pTestee!=*p2);
  delete p2;
}

PAT_C( PathTest, append_success ) {

  const std::string root = "aa/";
  m_pTestee->assign(root);
  m_pTestee->append("aaa");
  std::string a("aa/aaa");
  EXPECT_TRUE(m_pTestee->native()=="aa/aaa");
  delete m_pTestee;
  m_pTestee = new Path("aa/");
  m_pTestee->append("/aaa");
  EXPECT_TRUE(m_pTestee->native()=="aa/aaa");
  delete m_pTestee;
  m_pTestee = new Path("aa");
  m_pTestee->append("/aaa");
  EXPECT_TRUE(m_pTestee->native()=="aa/aaa");
  delete m_pTestee;
  m_pTestee = new Path("aa");
  m_pTestee->append("aaa");
  EXPECT_TRUE(m_pTestee->native()=="aa/aaa");
}

PAT_C( PathTest, should_become_generic_string ) {
  m_pTestee->assign("/etc/../dev/../usr//lib//");
  EXPECT_TRUE(0 == m_pTestee->generic_string().compare("/usr/lib/"));
}

PAT_C( PathTest, parent_path ) {
  m_pTestee->assign("aa/bb/cc/dd");
  EXPECT_TRUE(0 == m_pTestee->parent_path().compare("aa/bb/cc"));
  delete m_pTestee;
  m_pTestee = new Path("/aa/bb/");
  EXPECT_TRUE(0 == m_pTestee->parent_path().compare("/aa/bb"));
  delete m_pTestee;
  m_pTestee = new Path("/aa/bb");
  EXPECT_TRUE(0 == m_pTestee->parent_path().compare("/aa"));
  delete m_pTestee;
  m_pTestee = new Path("aa/");
  EXPECT_TRUE(0 == m_pTestee->parent_path().compare("aa"));
  delete m_pTestee;
  m_pTestee = new Path("aa");
  EXPECT_TRUE(m_pTestee->parent_path().empty());
}

PAT_C(PathTest, filename) {
  m_pTestee->assign("aa/bb/cc");
  EXPECT_TRUE(0 == m_pTestee->filename().compare("cc"));

  m_pTestee->assign("aa/bb/");
  EXPECT_TRUE(0 == m_pTestee->filename().compare(""));

  m_pTestee->assign("aa");
  EXPECT_TRUE(0 == m_pTestee->filename().compare("aa"));
}
