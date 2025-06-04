import os
from collections import deque

def solve(Co, Cc, Co1, Co2, Cg1, Cg2, T):
    best = 0
    # state if (ore, clay, obsidian, geodes, r1, r2, r3, r4, time)
    S = (0, 0, 0, 0, 1, 0, 0, 0, T)
    Q = deque([S])
    SEEN = set()
    while Q:
        state = Q.popleft()
        o,c,ob,g,r1,r2,r3,r4,t = state

        best = max(best, g)
        if t==0:
            continue
        
        # We get the maximum amount of ore we could possibly spend during any turn
        Core = max([Co, Cc, Co1, Cg1])

        # If we have more material than we would need, we cap the value to help set recognition
        if o >= t * Core - r1 * (t-1):
            o = t * Core - r1 * (t-1)
        if c >= t * Co2 - r2 * (t-1):
            c = t * Co2 - r2 * (t-1)
        if ob >= t * Cg2 - r3 * (t-1):
            ob = t * Cg2 - r3 * (t-1)

        state = (o,c,ob,g,r1,r2,r3,r4,t)
        if state in SEEN:
            continue
        SEEN.add(state)

        # We then try doing nothing or making a robot if we have enough material
        # And we don't have too many robots
        Q.append((o+r1,c+r2,ob+r3,g+r4,r1,r2,r3,r4,t-1))
        if o>=Co and r1<Core:
            Q.append((o-Co+r1, c+r2, ob+r3, g+r4, r1+1,r2,r3,r4,t-1))
        if o>=Cc and r2<Co2:
            Q.append((o-Cc+r1, c+r2, ob+r3, g+r4, r1,r2+1,r3,r4,t-1))
        if o>=Co1 and c>=Co2 and r3<Cg2:
            Q.append((o-Co1+r1, c-Co2+r2, ob+r3, g+r4, r1,r2,r3+1,r4,t-1))
        if o>=Cg1 and ob>=Cg2:
            Q.append((o-Cg1+r1, c+r2, ob-Cg2+r3, g+r4, r1,r2,r3,r4+1,t-1))

    return best

def main(input_dir):
    input_file_path = os.path.join(os.path.dirname(__file__), "../" + input_dir +"/19.in")
    
    with open(input_file_path, 'r') as f:
        data = f.read().splitlines()

    quality_level_sum1 = 0
    quality_level_sum2 = 1
    for i, line in enumerate(data):
        words = line.split()
        id_ = int(words[1][:-1]) # id of the blueprint
        ore_cost = int(words[6])
        clay_cost = int(words[12])
        obsidian_cost_ore, obsidian_cost_clay = int(words[18]), int(words[21])
        geode_cost_ore, geode_cost_clay = int(words[27]), int(words[30])
        best = solve(ore_cost, clay_cost, obsidian_cost_ore, obsidian_cost_clay, geode_cost_ore, geode_cost_clay, 24)
        quality_level_sum1 += id_ * best
        if i<3:
            s2 = solve(ore_cost, clay_cost, obsidian_cost_ore, obsidian_cost_clay, geode_cost_ore, geode_cost_clay,32)
            quality_level_sum2 *= s2

    print(f"Part 1: {quality_level_sum1}")
    print(f"Part 2: {quality_level_sum2}")
