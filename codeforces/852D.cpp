class UserMainCode
{
    public String keypadDecoder(String input1, int input2, int input3){

        String[] map = {"", "", "ABC", "DEF", "GHI", "JKL", "MNO", "PQRS", "TUV", "WXYZ"};
        int n = input2;
        
        if (n == 0) return "";

        long[] blockSize = new long[n];
        blockSize[n - 1] = 1; 
        
        for (int i = n - 2; i >= 0; i--) {
            int digit = input1.charAt(i + 1) - '0';
            long nextBlockSize = blockSize[i + 1] * map[digit].length();
            
            if (nextBlockSize > Integer.MAX_VALUE * 2L) {
                blockSize[i] = Integer.MAX_VALUE * 2L;
            } else {
                blockSize[i] = nextBlockSize;
            }
        }
        
        StringBuilder result = new StringBuilder();
        long k = input3 - 1;
        
        for (int i = 0; i < n; i++) {
            int digit = input1.charAt(i) - '0';
            String chars = map[digit];
            
            long currentBlockSize = blockSize[i];
            
            int charIndex = (int) (k / currentBlockSize);
            
            result.append(chars.charAt(charIndex));
            
            k %= currentBlockSize;
        }
        
        return result.toString();
    }
}