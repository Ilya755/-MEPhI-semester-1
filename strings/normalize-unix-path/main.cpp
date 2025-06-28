#include "task.h"

#include <nuclear/nuclear.h>

#include <cassert>

void ::nuclear::RunTests() {
    assert(normalize("/../../foo/././bar/../bar/./baz//1.txt") == "/foo/bar/baz/1.txt");
    assert(normalize("../../foo/././bar/../bar/./baz//1.txt") == "../../foo/bar/baz/1.txt");
    assert(normalize("..") == "..");
    assert(normalize(".") == ".");
    assert(normalize("/.") == "/");
    assert(normalize("/..") == "/");
    assert(normalize("/../.") == "/");
    assert(normalize("../.") == "..");
    assert(normalize("file.txt") == "file.txt");
}
