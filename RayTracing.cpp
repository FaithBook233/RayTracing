
#include <iostream>

int main()
{
    int nx = 200;//图片宽度（单位为像素）
    int ny = 100;//图片宽度（单位为像素）
    //文件头写入
    std::cout << "P3" << std::endl << nx << " " << ny << std::endl << "255" << std::endl;
    
    for (int j = ny - 1; j >= 0; j--)//行信息
    {
        for (int i = 0; i < nx; i++)//列信息
        {
            //注意原书上的类型为float，以后的代码中会整体采用double
            //计算每个像素上的RGB信息
            double r = double(i) / double(nx);
            double g = double(j) / double(ny);
            //每个像素的蓝色通道固定为0.2
            double b = 0.2;
            //因为ppm文件中RGB通道值为0-255，而上面计算出来的r,g,b范围为0-1，这里进行转换
            int ir = int(255.99 * r);
            int ig = int(255.99 * g);
            int ib = int(255.99 * b);
            //将当前像素的三个通道值写入文件
            std::cout << ir << " " << ig << " " << ib << std::endl;
        }
    }
}
