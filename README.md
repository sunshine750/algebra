# algebra

![photo](https://github.com/sunshine750/img_bed/blob/main/1.png)

![photo2](https://github.com/sunshine750/img_bed/blob/main/2.png)

`add_matrix`、`sub_matrix`、`mul_matrix`、`scale_matrix`、`transpose_matrix`、`trace_matrix`功能正常

`det_matrix`、`inv_matrix`、`rank_matrix`功能正常

在计算行列式和逆矩阵时，使用了递归的方式，这种方法简洁且符合数学定义，特别是使用拉普拉斯展开法（用于行列式计算）和代数余子式（用于逆矩阵计算）。
使用 memset 来初始化矩阵数据，这在 C 语言中是一个高效的方式，可以快速将矩阵元素设置为零。
在矩阵操作中，每个函数都直接处理并返回矩阵结构，使得调用这些操作时更加直观、简洁。
要求相加的矩阵必须有相同的行列数，乘法时列数和行数需匹配，求逆时必须是方阵且非奇异。
