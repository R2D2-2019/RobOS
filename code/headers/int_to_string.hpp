#pragma once

namespace r2d2::robos {

    /**
     * Add the prefix to the output stream.
     *
     * @internal
     * @param str
     * @param base
     * @return
     */
    constexpr int _add_prefix(char *str, int base) {
        char *p = str;

        if (base == 8) {
            *p++ = 'b';
            *p = '0';

            return 2;
        }

        if (base == 16) {
            *p++ = 'x';
            *p = '0';

            return 2;
        }

        return 0;
    }

    constexpr void _reverse(char *str, const int length) {
        int start = 0;
        int end = length - 1;

        while (start < end) {
            char temp = *(str + start);
            *(str + start++) = *(str + end);
            *(str + end--) = temp;
        }
    }

    /**
     * converts an int to a string, stores the string in the supplied char*
     *
     * @internal
     * @param num
     * @param str
     * @param base
     * @return
     */
    constexpr char *int_to_str(int num, char *str, int base = 10) {
        // Handle 0 explicitly, otherwise empty string is printed for 0
        if (num == 0) {
            str[0] = '0';
            int added = _add_prefix(&str[1], base);

            str[added + 1] = '\0';

            return str;
        }

        int i = 0;
        bool negative = false;

        // In standard itoa(), negative numbers are handled only with
        // base 10. Otherwise numbers are considered unsigned.
        if (num < 0 && base == 10) {
            negative = true;
            num = -num;
        }

        // Process individual digits
        while (num != 0) {
            int rem = num % base;

            if (rem > 9) {
                str[i++] = 'A' + (rem - 10);
            } else {
                str[i++] = '0' + rem;
            }

            num /= base;
        }

        // If number is negative, append '-'
        if (negative) {
            str[i++] = '-';
        }

        // For hex, append 0x
        int added = _add_prefix(&str[i], base);
        str[i += added] = '\0'; // Append string terminator

        // Reverse the string
        _reverse(str, i);

        return str;
    }
} // namespace r2d2::robos