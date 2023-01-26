#include <VectorService.hpp>
#include <limits>

ParsedColor::ParsedColor (FreeVector vec) : 
        ParsedColor{static_cast<char>(vec.x() * 255), 
                    static_cast<char>(vec.y() * 255),
                    static_cast<char>(vec.z() * 255),
                    std::numeric_limits<char>::max()}
    {}

/*
    Clamp value to [0;1] range
*/
double clamp(double val)
{
    if  (val < 0)
    {
        return 0;
    }
    else if (val <= 1) 
    {
        return val;
    }

    return 1;
}

ParsedColor whitescale (float coef) // 1 - totally white, 0 - totally black
{
    char grayscale = 255.0 * (coef);
    return ParsedColor{grayscale, grayscale, grayscale, (char) 0xFF};
}

std::ostream& operator<< (std::ostream& cout, ParsedColor clr)
{
    cout  << '{' <<
    int(clr.r) << ' ' <<
    int(clr.g) << ' ' <<
    int(clr.b) << ' ' <<
    int(clr.a) << '}' << std::endl;

    return cout;
}