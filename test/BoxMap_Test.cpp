// ++--++
// @file BoxMap_Test.cpp
// @date Created: <07-04-16>
// @version <1.0.0>
//
// @author Sander Kolman
//
// @section LICENSE
// License: newBSD
//
// Copyright � 2016, HU University of Applied Sciences Utrecht.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
// - Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
// - Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
// - Neither the name of the HU University of Applied Sciences Utrecht nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE HU UNIVERSITY OF APPLIED SCIENCES UTRECHT
// BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
// GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
// OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// ++--++

#include "../source/include/BoxMap.hpp"
#include "gtest/gtest.h"
#include <iostream>
#include <random>
#include <time.h>

/*
* Constructor
*/
TEST(BoxMap, DefaultConstructor){
    r2d2::BoxMap bm{};
    ASSERT_EQ(bm.get_map_size(), 0);
}

/*
* BoxMap::set_box_info() test
*/
TEST(BoxMap, AddBox){
    r2d2::BoxMap bm{};
    bm.set_box_info(Box{}, r2d2::BoxInfo{});
    ASSERT_EQ(bm.get_map_size(), 1);
}

/*
* BoxMap::get_box_info() test
*/
TEST(BoxMap, GetBoxInfo1){
    srand(time(NULL));
    r2d2::BoxMap bm{};
    for (int i = 0; i < 5; i++){

        r2d2::BoxInfo temp{
            rand() % 2 == 0,
            rand() % 2 == 0,
            rand() % 2 == 0
        };

        bm.set_box_info(
            Box{
            Coordinate{},
            Coordinate{
                2 * Length::METER,
                2 * Length::METER,
                2 * Length::METER
            }
        }, temp);

        ASSERT_EQ(
            bm.get_box_info(
            Box{
            Coordinate{
                0.5*Length::METER,
                0.5*Length::METER,
                0.5*Length::METER
            },
            Coordinate{
                    1.5*Length::METER,
                    1.5*Length::METER,
                    1.5*Length::METER
                }
        }
        ),
        temp
        );
    }
}


/*
* BoxMap::get_box_info() test
*/
TEST(BoxMap, GetBoxInfo2){
    srand(time(NULL));
    r2d2::BoxMap bm{};

    bm.set_box_info(
        Box{
        Coordinate{
            rand() % 20 * Length::METER,
            rand() % 20 * Length::METER,
            rand() % 20 * Length::METER
        },
        Coordinate{
                rand() % 20 * Length::METER,
                rand() % 20 * Length::METER,
                rand() % 20 * Length::METER
            }
    },
    r2d2::BoxInfo{ false, true, false }
                );

    bm.set_box_info(
        Box{
        Coordinate{
            rand() % 20 * Length::METER,
            rand() % 20 * Length::METER,
            rand() % 20 * Length::METER
        },
        Coordinate{
                rand() % 20 * Length::METER,
                rand() % 20 * Length::METER,
                rand() % 20 * Length::METER
            }
    },
    r2d2::BoxInfo{ false, false, true }
                );

    ASSERT_EQ(
        bm.get_box_info(
        Box{
        Coordinate{
            0 * Length::METER,
            0 * Length::METER,
            0 * Length::METER
        },
        Coordinate{
                20 * Length::METER,
                20 * Length::METER,
                20 * Length::METER
            }
    }
    ),
    (r2d2::BoxInfo{ false, true, true })
    );
}

/*
* BoxMap::get_bounding_box() test
*/
TEST(BoxMap, BoundingBox){
    r2d2::BoxMap bm{};

    bm.set_box_info(
        Box{
        Coordinate{
            10 * Length::METER,
            10 * Length::METER,
            10 * Length::METER
        },
        Coordinate{
                20 * Length::METER,
                20 * Length::METER,
                20 * Length::METER
            }
    },
    r2d2::BoxInfo{ false, true, true }
                );

    bm.set_box_info(
        Box{
        Coordinate{
            15 * Length::METER,
            15 * Length::METER,
            15 * Length::METER
        },
        Coordinate{
                60 * Length::METER,
                60 * Length::METER,
                60 * Length::METER
            }
    },
    r2d2::BoxInfo{ false, false, true }
                );

    Box bounding = bm.get_map_bounding_box();

    ASSERT_TRUE(
        (bounding.get_bottom_left().get_x() / Length::METER == 10) &&
        (bounding.get_bottom_left().get_y() / Length::METER == 10) &&
        (bounding.get_bottom_left().get_z() / Length::METER == 10) &&
        (bounding.get_top_right().get_x() / Length::METER == 60) &&
        (bounding.get_top_right().get_y() / Length::METER == 60) &&
        (bounding.get_top_right().get_z() / Length::METER == 60)
        );
}

/*
* Real world test / stress test
*/
TEST(BoxMap, UsageExample){
    std::uniform_real_distribution<double> random_real(-100.0, 100.0);
    std::default_random_engine re(time(NULL));
    srand(time(NULL));
    r2d2::BoxMap bm{};
    cout << "May take a minute or 2...\n";

    for (int i = 0; i < 50; i++){
        bm.set_box_info(
            Box{
            Coordinate{
                random_real(re)*Length::METER,
                random_real(re)*Length::METER,
                random_real(re)*Length::METER
            },
            Coordinate{
                    random_real(re)*Length::METER,
                    random_real(re)*Length::METER,
                    random_real(re)*Length::METER
                }
        },
        r2d2::BoxInfo{ rand() % 2 == 0, rand() % 2 == 0, rand() % 2 == 0 }
                    );
    }
    ASSERT_GT(bm.get_map_size(), 9);
    ASSERT_TRUE(
        (bm.get_box_info(bm.get_map_bounding_box())
        == r2d2::BoxInfo{ true, true, true })
        );

    Box bounding = bm.get_map_bounding_box();
    ASSERT_TRUE(
        (bounding.get_bottom_left().get_x() / Length::METER < 0) &&
        (bounding.get_bottom_left().get_y() / Length::METER < 0) &&
        (bounding.get_bottom_left().get_z() / Length::METER < 0) &&
        (bounding.get_top_right().get_x() / Length::METER > 0) &&
        (bounding.get_top_right().get_y() / Length::METER > 0) &&
        (bounding.get_top_right().get_z() / Length::METER > 0)
        );
}