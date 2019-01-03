def print_diff(sign, prefix, key, val):
    if type(val) == dict:
        for k, v in val.items():
            print_diff(sign, prefix + "." + key, k, v)
    else:
        print("%s$%s.%s:%s" % (sign, prefix, key, val))


def json_diff(left, right, prefix=""):
    for key, val in left.items():
        if not key in right:
            print_diff("-", prefix, key, val)
            continue
        if left[key] == right[key]:
            continue
        if type(val) == dict and type(right[key]) == dict:
            json_diff(left[key], right[key], prefix + "." + key)
        else:
            print_diff("-", prefix, key, val)
            print_diff("+", prefix, key, right[key])

    for key, val in right.items():
        if not key in left:
            print_diff("+", prefix, key, val)
            continue


def main():

    left = {
        "a": 1,
        "b": 2,
        "c": 3,
    }

    right = {
        "a": 1,
        "b": 22,
    }

    left_object = {
        "a": 1,
        "b": 2,
        "c": {
            "y": 3,
            "f": "kkkkkkk",
            "e": {
                "u": 1,
                },
            },
    }
    
    right_object_similar = {
        "a": 1,
        "b": 2,
        "c": {
            "y": 3,
            "f": "kkkkkkk",
            "e": {
                "u": 13,
                },
            },
    }
    
    right_object = {
        "a": 1,
        "b": 22,
        "c": {
            "y": 3,
            "z": "A",
            },
    }
    
    json_diff(left_object, right_object_similar)


main()
