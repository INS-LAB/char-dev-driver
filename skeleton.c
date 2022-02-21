#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>	//strcut file_operations 헤더파일
#include <linux/uaccess.h>
#include <linux/slab.h>
 
// skeleton_device_driver

static char *buffer = NULL;

// file_operations에서 .open으로 불러올 함수
//즉, 디바이스 파일이 열릴시 불러오는 함수
int skeleton_open(struct inode *inode, struct file *filp) {
    printk(KERN_ALERT "skeleton_device open function called\n");

    return 0;
}
 
// file_operations에서 .release로 불러올 함수
//즉, 디바이스 파일이 닫힐시 불러오는 함수
int skeleton_release(struct inode *inode, struct file *filp) {
    printk(KERN_ALERT "skeleton_device release function called\n");

    return 0;
}
 
// file_operations에서 .write로 불러올 함수
//즉, 디바이스 파일내에 write할 시 불러오는 함수
//ssize_t 타입 -> 시스템 명령어 형식타입(64bit cpu일시 64bit를 가짐)
//linux명령어인 getconf LONG_BIT로 확인가능
ssize_t skeleton_write(struct file *filp, const char *buf, size_t count, loff_t *f_pos) {
    printk(KERN_ALERT "skeleton_device write function called\n");
    strcpy(buffer, buf); //응용프로그램에서 불러온 buf를 buffer에 저장

    return count;
}
 
// file_operations에서 .read로 불러올 함수
//즉, 디바이스 파일내의 data를 read할 시 불러오는 함수
ssize_t skeleton_read(struct file *filp, char *buf, size_t count, loff_t *f_pos) {
    printk(KERN_ALERT "skeleton_device read function called\n");
    copy_to_user(buf, buffer, 1024); //응용프로그램으로 버퍼를 내보내는 함수

    return count;
}
 
// file_operations에서 사용할 멤버들
// 각 해당하는 함수와 연결하는 모습을 볼 수 있다.
static struct file_operations skeleton_fops = {
    .read = skeleton_read, 
    .write = skeleton_write,
    .open = skeleton_open,
    .release = skeleton_release
};
 
// insmod명령어로 커널에 부착시킬때 불러올 함수
int __init skeleton_init(void) {
    if(register_chrdev(300, "skeleton_device", &skeleton_fops) < 0 )
        printk(KERN_ALERT "driver init failed\n"); 
    else
        printk(KERN_ALERT "driver init successful\n");
    buffer = (char*)kmalloc(1024, GFP_KERNEL); //buffer가 사용자영역의 메모리를 가르키게해주는 kmalloc
    if(buffer != NULL) 
        memset(buffer, 0, 1024);
    return 0;
}
 
// rmmod명령어로 커널에서 모듈을 제거할시 불러올 함수
void __exit skeleton_exit(void) {
    unregister_chrdev(300, "skeleton_device");
    printk(KERN_ALERT "driver cleanup successful\n");
    kfree(buffer);
}

module_init(skeleton_init); //모듈부착시 실행 module_init
module_exit(skeleton_exit); //모듈제거시 실행 module_exit

MODULE_LICENSE("GPL"); //모듈의 라이센스 -> GPL