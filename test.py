import matplotlib.pyplot as plt
import numpy as np
plt.rcParams['font.sans-serif'] = ['SimHei']
# 数据
test_cases = [
    "ATC", "DME", "TCAS", "VHF", "作动筒端头", "充氧盖板", "右侧着陆灯", "右侧转弯灯", 
    "指点信标点", "排水杆", "机外放养指示器", "机身下部防撞灯", "气门嘴", "滑行灯", 
    "着陆灯", "缓冲支柱", "舱门和口盖", "起飞灯", "轮毂", "轮胎"
]

correct_rates = [
    96, 98, 96, 100, 98, 100, 96, 94, 98, 100, 96, 100, 98, 94, 100, 96, 98, 100, 96, 98
]

# 创建柱状图
plt.figure(figsize=(12, 8))
plt.bar(test_cases, correct_rates, color='skyblue')

# 添加标题和标签
plt.title('测试用例正确率', fontsize=16)
plt.xlabel('测试用例', fontsize=14)
plt.ylabel('正确率 (%)', fontsize=14)

# 旋转x轴标签以避免重叠
plt.xticks(rotation=90)

# 显示网格
plt.grid(axis='y', linestyle='--', alpha=0.7)

# 显示图表
plt.tight_layout()
plt.show()

