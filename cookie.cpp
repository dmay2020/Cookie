/*

    Cookie v0.1a
    cookie.cpp
    Copyright (c) 2023 Derek May


    This program is provided without any warranty of any kind.
    The author cannot be held liable for any damages arising from the use of this program.


    Permission is granted to anyone to use this software for any legal purpose,
    and to alter or redistribute it freely, given the following:

        1. You may not claim this work as your own. When modifying, clear acknowledgment is required.
        2. Versions altered from the original must be clearly marked as altered.
        3. This notice cannot be removed or altered from any altered version or redistribution.


    Includes unmodified use of the following:

        LodePNG version 20221108                     : https://github.com/lvandeve/lodepng : Copyright (c) 2005-2022 Lode Vandevenne

        Dirent interface for Microsoft Visual Studio : https://github.com/tronkko/dirent   : Copyright (C) 1998-2019 Toni Ronkko

*/

/*
    
    Cookie:
    (cookie.cpp)

    A free and open-source console-based program which finds and flags empty masks.

*/

#include <iostream>
#include <vector>
#include "dirent.h"
#include "lodepng.h"

#define IMAGE_FOLDER_PATH "images/"
#define PROGRAM_NAME "cookie.cpp"

bool check_for_any_value(std::vector<unsigned char> im) {
    for (int i = 0; i < im.size() - 1; i += 4) {
        if (im[i] || im[i + 1] || im[i + 2]) return false;
    }   return true;
}

bool check_file(std::string fn) {
    fn = IMAGE_FOLDER_PATH + fn;
    std::vector<unsigned char> image_RGBA;
    unsigned int width, height;
    unsigned int error = lodepng::decode(image_RGBA, width, height, fn);
    if (error) {
        std::cout << "\"lodepng\" Error. Try making sure all files in \"" << IMAGE_FOLDER_PATH << "\" are .png files: " << error << std::endl;
        exit(1);
    }
    return check_for_any_value(image_RGBA);
}

std::vector<std::string> get_filenames() {
    std::vector<std::string> filenames;
    DIR* dir;
    struct dirent* ent;
    dir = opendir(IMAGE_FOLDER_PATH);
    if (dir == NULL) {
        std::cout << "Could not open image folder.\nTry making sure the folder \"" << IMAGE_FOLDER_PATH << "\" is in the same directory as " << PROGRAM_NAME << " and all other files." << std::endl;
        exit(1);
    }
    while ((ent = readdir(dir)) != NULL) {
        std::string filename(ent->d_name);
        if (filename != "." && filename != "..") {
            if (check_file(filename)) {
                filenames.push_back(filename);
            }
        }
    }
    closedir(dir);
    return filenames;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> filenames = get_filenames();

    if (filenames.size() == 0) {
        std::cout << "All files have at least 1 non-black pixel OR no files were present." << std::endl;
        return 0;
    }

    std::cout << "Filenames:" << std::endl;
    for (int i = 0; i < filenames.size(); i++) {
        std::cout << filenames[i] << std::endl;
    }

    return 0;
}
