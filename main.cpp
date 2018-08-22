#include <iostream>
#include "DirUtils.h"
#include "BMPImage.h"

using namespace std;

int main(int argc, char **argv)
{
    // get the cwd of the excutable
    string cwd = DirUtils::getcwd();

    // create the output folder
    DirUtils::dirCreate(cwd + "\\Output");

    // get all input files
    vector<string> files = DirUtils::getFiles(cwd + "\\Input");

    // create an object of BMPImage class and make it load the logo file
    BMPImage logo(DirUtils::getFiles(cwd + "\\Logo")[0]);

    // NOTE: Storing the size of the container instead of calling this method
    // for each iteration IS WAY FASTER THEN I THOUGHT
    int fs = files.size();
    for(int f = 0; f < fs; f++)
    {
        //cout << f << "/" << files.size() << "\n";
        // load the current input file
        BMPImage img(files[f]);
        //cout << img.w << " " << img.h << "\n";

        // find all regions which can store the wenglor's logo
        vector<Rect> regions = img.getWhiteSpots(logo.w, logo.h);
        //cout << regions.size() << "\n";
        // for each region, use the copyLogo method to copy the logo in that region
        for(int i = 0; i < regions.size(); i++)
        {
            img.copyLogo(logo, regions[i]);
        }

        // after that save the altered image
        img.save(cwd + "\\Output\\output_" + to_string(f + 1) + ".bmp");
    }
}
