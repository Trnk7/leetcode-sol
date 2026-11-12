class Solution {
public:

string threeDigit(int n) {
    string once[] = {"One","Two","Three","Four","Five","Six","Seven","Eight","Nine"};
    string elv[] = {"Ten","Eleven","Twelve","Thirteen","Fourteen","Fifteen","Sixteen","Seventeen","Eighteen","Nineteen"};
    string tens[] = {"Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety"};

    string words = "";

    int c = n % 10;
    int b = (n / 10) % 10;
    int a = (n / 100) % 10;

    if (a) {
        words = once[a - 1] + " Hundred";
    }

    if (b) {
        if (b != 1) {
            if (!words.empty()) words += " ";
            words += tens[b - 2];
        } else {
            if (!words.empty()) words += " ";
            words += elv[c];
            return words;
        }
    }

    if (c) {
        if (!words.empty()) words += " ";
        words += once[c - 1];
    }

    return words;
}

string numberToWords(int num) {
    if (num == 0) return "Zero";

    string other[] = {"", "Thousand", "Million", "Billion"};

    string words = "";
    int i = 0;

    while (num) {
        int d = num % 1000;
        string s = threeDigit(d);

        if (!s.empty()) {
            string group = s;

            if (i > 0) {
                group += " " + other[i];
            }

            if (words.empty()) {
                words = group;
            } else {
                words = group + " " + words;
            }
        }

        i++;
        num /= 1000;
    }

    return words;
}

};