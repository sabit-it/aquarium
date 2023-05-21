
std::string generate_path(const std::string& path, int& n){
    n++;
    return path + std::to_string(n) + "jpg";
}