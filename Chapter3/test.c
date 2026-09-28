#include <stdio.h>
#include <stdint.h>

#define likely(x) __buildin_expect(!!(x), 1)
#define unlikely(x) __buildin_expect(!!(x), 0)
uint64_t read_tsc() {
    unsigned int low, high;
    // BẮT BUỘC phải có dấu ngoặc kép "" quanh "rdtsc", "=a" và "=d"
    asm volatile("rdtsc" : "=a" (low), "=d" (high));
    
    // Gộp 32-bit cao và 32-bit thấp thành một số 64-bit duy nhất
    return ((uint64_t)high << 32) | low;
}

int main() {
    uint64_t start, end;
    volatile int sum = 0; // Sử dụng volatile để ép CPU phải thực hiện vòng lặp

    // 1. Chụp số chu kỳ xung nhịp trước khi chạy
    start = read_tsc();

    // Đoạn mã cần đo hiệu năng
    for (int i = 0; i < 1000000; i++) {
        sum += i;
    }

    // 2. Chụp số chu kỳ xung nhịp sau khi chạy xong
    end = read_tsc();

    // 3. Tính toán và in kết quả (BẮT BUỘC chuỗi định dạng phải nằm trong "")
    uint64_t cycles_elapsed = end - start;
    printf("Tong tinh duoc: %d\n", sum);
    printf("So chu ky CPU tieu ton: %llu chu ky\n", (unsigned long long)cycles_elapsed);

    return 0;
}

