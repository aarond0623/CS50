def luhn_check(cc_number):
    """Performs a Luhn check on a credit card number using the Luhn algorithm.

    The Luhn algorithm doubles the value of every second digit, starting from
    t, and replaces that digit with the sum of that value. Then, all digits
    are summed together. If the sum is equal to 0 mod 10, the number passes
    the Luhn check.

    Args:
        cc_number: A credit card number.

    Returns:
        True if the number passes. False if it fails or the number is invalid.

    """
    cc_number = str(cc_number)
    cc_len = len(cc_number)
    check_sum = 0
    for i in range(cc_len):
        # Get the position from the right
        position = cc_len - i
        try:
            digit = int(cc_number[i])
        except ValueError:
            return False
        if position % 2 == 0:
            digit *= 2
            if digit >= 10:
                # If the sum is 2 digits (10-18), the sum of the digits is the
                # sum minus 9.
                digit -= 9
        check_sum += digit

    return check_sum % 10 == 0


def cc_type(cc_number):
    """Prints the type of a credit card number.

    Will print one of "AMEX", "VISA", or "MASTERCARD". If the type is none of
    these, the function prints "INVALID".

    Args:
        cc_number: A credit card number.

    """
    # Perform a Luhn check to make sure the number is valid:
    if not luhn_check(cc_number):
        print("INVALID")
        return

    cc_number = str(cc_number)
    cc_len = len(cc_number)
    # The first two digits
    start = cc_number[0:2]

    # AMEX starts with 34 or 37
    if cc_len == 15 and start in ['34', '37']:
        print("AMEX")
    # Mastercard starts with 51-55
    elif cc_len == 16 and start in [str(x) for x in range(51, 56)]:
        print("MASTERCARD")
    # Visa starts with 40-49
    elif cc_len == 16 and start in [str(x) for x in range(40, 50)]:
        print("VISA")
    else:
        print("INVALID")


if __name__ == '__main__':
    # Get a number.
    while True:
        cc_number = input("Number: ")
        try:
            int(cc_number)
            assert int(cc_number) >= 0
            break
        except (ValueError, AssertionError):
            pass

    cc_type(cc_number)
