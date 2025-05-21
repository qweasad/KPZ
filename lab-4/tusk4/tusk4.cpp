#include <iostream>
#include "LightImageNode.h"
#include "FileSystemLoadStrategy.h"
#include "NetworkLoadStrategy.h"

std::unique_ptr<ImageLoadStrategy> chooseStrategy(const std::string& href) {
    if (href.find("http://") == 0 || href.find("https://") == 0) {
        return std::make_unique<NetworkLoadStrategy>();
    }
    return std::make_unique<FileSystemLoadStrategy>();
}

int main() {
    LightImageNode localImage("C:/images/picture.jpg", chooseStrategy("C:/images/picture.jpg"), "Local image");
    std::cout << localImage.outerHTML() << std::endl;
    std::cout << localImage.loadImage() << std::endl;

    LightImageNode networkImage("http://example.com/image.jpg", chooseStrategy("http://example.com/image.jpg"), "Network image");
    std::cout << networkImage.outerHTML() << std::endl;
    std::cout << networkImage.loadImage() << std::endl;

    return 0;
}
