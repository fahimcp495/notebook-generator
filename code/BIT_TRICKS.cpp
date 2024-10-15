## Next Combination Mask
int next_combs_mask(int mask) {
  int lsb = -mask & mask;
  return (((mask + lsb) ^ mask) / (lsb << 2)) | (mask + lsb);
}
## Iterate over submask in decreasing order
for (int s=mask; s > 0; s = (s-1)&mask) {}
