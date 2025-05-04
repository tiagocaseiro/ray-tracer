#include <gtest/gtest.h>

#include <fstream>
#include <sstream>

#include "canvas.h"
#include "common.h"

// Demonstrate some basic assertions.
TEST(canvas, Ctor)
{
    canvas c{10, 20};

    EXPECT_EQ(c.width, 10);
    EXPECT_EQ(c.height, 20);

    for(const auto& pixel : c.get_pixels())
    {
        EXPECT_EQ(pixel, color::black());
    }
}

TEST(canvas, PaintPixel)
{
    canvas c{10, 20};

    c.paint_pixel(2, 3, color::red());

    EXPECT_EQ(c.pixel_at(2, 3), color::red());
}

TEST(canvas, SaveToFile)
{
    canvas c{10, 20};

    c.save_to_file("image.ppm");

    std::fstream file("image.ppm");
    std::string str;
    std::getline(file, str);
    EXPECT_EQ(str, "P3");
    std::getline(file, str);
    EXPECT_EQ(str, "10 20");
    std::getline(file, str);
    EXPECT_EQ(str, "255");
}

TEST(canvas, SaveToFileCheckColors)
{
    canvas c{5, 3};

    color c1 = {1.5f, 0.f, 0.f};
    color c2 = {0.f, 0.5f, 0.f};
    color c3 = {-0.5f, 0.f, 1.f};

    c.paint_pixel(0, 0, c1);
    c.paint_pixel(2, 1, c2);
    c.paint_pixel(4, 2, c3);
    c.save_to_file("image.ppm");

    std::fstream file("image.ppm");
    std::string str;

    std::getline(file, str);
    std::getline(file, str);
    std::getline(file, str);
    std::getline(file, str);

    EXPECT_EQ(str, "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0");
    std::getline(file, str);
    EXPECT_EQ(str, "0 0 0 0 0 0 0 127 0 0 0 0 0 0 0");
    std::getline(file, str);
    EXPECT_EQ(str, "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255");
}
