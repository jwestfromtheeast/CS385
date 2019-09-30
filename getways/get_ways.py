def get_ways(num_stairs):
    ways = []
    if num_stairs <= 0:
        ways.append([])
    else:
        for i in range(1, 4):
            if num_stairs >= i:
                result = get_ways(num_stairs - i)
                for j in range(len(result)):
                    result[j].append(i)
                ways += result
    return ways

print(get_ways(21))