class segmenter:
  
  def __init__(self):
    self.index_count = 0
    self.Tx_buff = []
    self.data = []

  def load_data(self,s):
    self.data = s

  def append_data(self,s):
    self.data.append(s)

  def prep_buff(self):
    self.index_count = 0
    l = len(self.data)
    diff = l - self.index_count
    if diff <= 0:
      self.Tx_buff = []
      return 0
    if diff>10:
      rem = 10
    else:
      rem = diff
    self.Tx_buff = self.data[self.index_count:self.index_count+rem]
    self.index_count = self.index_count + rem
    self.data = self.data[self.index_count:]
    return 1

  def generate_data(self):
    flag = self.prep_buff()
    ret = []
    if not flag:
      return ret
    else:
      for i in self.Tx_buff:
        for j in i:
          ret.append(j)
      return ret

"""
str=[[1, 1, 1, 1, 1, 1],[1, 0, 1, 0, 1, 1],[0, 1, 0, 1, 1, 0],[1, 1, 0, 0, 0, 0],[1, 1, 0, 1, 1, 1],[1, 0,0, 0, 1, 1],
     [1, 1, 1, 1, 1, 1],[1, 0, 1, 0, 1, 1],[0, 1, 0, 1, 1, 0],[1, 1, 0, 0, 0, 0],[1, 1, 0, 1, 1, 1],[1, 0,0, 0, 1, 1]]

SEG = segmenter()
SEG.load_data(str)
print(len(SEG.generate_data()))
print(len(SEG.generate_data()))
print(len(SEG.generate_data()))
"""
