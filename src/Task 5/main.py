def hunt(L, R):
    """
    Divide & Conquer: returns (forward_sweep, backward_sweep)
    that together guarantee catching the target in [L, R].

    Divide:  split [L, R] at midpoint
    Conquer: recursively get forward/backward sweeps for each half
    Combine: merge half-sweeps into full sweeps, then concatenate
    """
    if L > R:
        return [], []
    if L == R:
        return [L], [L]

    mid = (L + R) // 2

    left_fwd, left_bwd   = hunt(L, mid)
    right_fwd, right_bwd = hunt(mid + 1, R)

    # Combine step:
    forward  = left_fwd  + right_fwd    # [L → mid] + [mid+1 → R]
    backward = right_bwd + left_bwd     # [R → mid+1] + [mid → L]

    return forward, backward


def build_sequence(n):
    if n <= 2:
        return [1] * n
    fwd, bwd = hunt(2, n - 1)       # only sweep interior positions
    return fwd + bwd                 # forward sweep + backward sweep


def verify(n, sequence):
    """Correct verifier: tracks all possible surviving positions"""
    possible = set(range(1, n + 1))
    for shot in sequence:
        possible.discard(shot)
        new_possible = set()
        for pos in possible:
            if pos - 1 >= 1: new_possible.add(pos - 1)
            if pos + 1 <= n: new_possible.add(pos + 1)
        possible = new_possible
    return len(possible) == 0


for n in range(2, 17):
    seq = build_sequence(n)
    result = verify(n, seq)
    print(f"N={n:2d} | Shots={len(seq):2d} | {'✓' if result else '✗'} | {seq}")