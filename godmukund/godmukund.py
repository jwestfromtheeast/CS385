import re
from matplotlib import pyplot as plt
from numpy import array
ALPHA = 0.8

p = re.compile('[+-]?([0-9]*[.])?[0-9]+')
with open('RAWDATA') as f:
    content = f.readlines()
# you may also want to remove whitespace characters like `\n` at the end of each line
content = [x.split()[7] for x in content]
content = [re.findall(r"[-+]?\d*\.\d+|\d+", x) for x in content]
content = [item for sublist in content for item in sublist]
content = [float(content[i]) for i in range(10000)]
print(len(content))
content_processed = []
content_processed.append(content[0])
RTT_old = content_processed[0]
for i in range(1, len(content)):
    content_processed.append(ALPHA * RTT_old + (1 - ALPHA) * content[i])
    RTT_old = content_processed[-1]
idx = [x for x in range(1, len(content) + 1)]

plt.plot(content)
plt.plot(content_processed)
plt.legend(['Raw RTT', 'EWMA RTT'])
plt.xlabel('Sample Number')
plt.ylabel('Delay (ms)')
plt.show()