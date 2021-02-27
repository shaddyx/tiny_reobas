int calc_percentage(int temp, int min_temp, int max_temp){
    if (temp >= max_temp){
        return 100;
    }
    if (temp <= min_temp){
        return 0;
    }
    return ((temp - min_temp) * 100) * (100 / (max_temp - min_temp)) / 100;
}