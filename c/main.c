#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define GRUB_CONF_FILE                  "/tmp/rootdir/boot/grub/grub.conf"
#define DEVICE_MAP_FILE                 "/tmp/rootdir/boot/grub/device.map"
#define STRING_LENGTH                   80
#define SHORT_STRING_LENGTH             10
#define DEV_LENGTH                      8
#define PARTITION_LENGTH                64
#define GRUB_PARTITION_LENGTH           64
#define IDE_NUM                         8
#define SCSI_NUM                        16
#define LINEMAX                         128

// return 0 if ok
// -1 if error
int adjust_grub_device_map(const char *boot_partition)
{
    FILE *fp = NULL;
    char *disk[IDE_NUM + SCSI_NUM];
    char buf[LINEMAX];
    char boot_device[DEV_LENGTH + 1];
    int i, j;
    int found = 0;
    char *p = NULL;

    for (i = 0; i < IDE_NUM + SCSI_NUM; ++i) {
        disk[i] = NULL;
    }

    if (boot_partition == NULL) {
        fprintf(stderr, "%s %d %s boot_partition is NULL\n", __FILE__, __LINE__, __func__);
        return -1;
    }
    strncpy(boot_device, boot_partition, DEV_LENGTH);
    boot_device[DEV_LENGTH] = '\0';

    // swap "(hd0)  /dev/sda" with "(hd0) /dev/sdb" if sdb is the BIOS boot disk
    if ((fp = fopen(DEVICE_MAP_FILE, "r")) == NULL ) {
	    fprintf(stderr, "fopen DEVICE_MAP_FILE error ");
	    return -1;
    }
    
    i = 0;
    memset(buf, '\0', LINEMAX);
    while (fgets(buf, LINEMAX, fp) != NULL) {
        if (buf[0] == '#') {
            continue;
        }
        
        if (strstr(buf, "\n") == NULL) {
            continue;
        }

        if (strstr(buf, "hd") == NULL) {
            continue;
        }

        p = NULL;
        if ((p = strchr(buf, '/')) != NULL) {
            disk[i] = (char *)malloc(PARTITION_LENGTH);
            memset(disk[i], '\0', PARTITION_LENGTH);
            strncpy(disk[i], p, PARTITION_LENGTH);
            ++i;
            memset(buf, '\0', LINEMAX);
        }
    }

    fclose(fp);

    for (i = 0; i < IDE_NUM + SCSI_NUM; ++i) {
        if (disk[i] != NULL) {
            if (strstr(disk[i], boot_device) != NULL) {
                found = 1;
                char tmp[PARTITION_LENGTH];
                memset(tmp, '\0', PARTITION_LENGTH);
                strncpy(tmp, disk[0], PARTITION_LENGTH);
                strncpy(disk[i], disk[0], PARTITION_LENGTH);
                strncpy(disk[0], boot_device, DEV_LENGTH);
            }
        }
    }
    
    if (found != 1) {
        fprintf(stderr, "%s %d %s not found error\n", __FILE__, __LINE__, __func__);
        return -1;
    }
        
    if ((fp = fopen(DEVICE_MAP_FILE, "w+")) == NULL ) {
	    fprintf(stderr, "fopen DEVICE_MAP_FILE error ");
	    return -1;
    }
    
    for (i = 0; i < IDE_NUM + SCSI_NUM; ++i) {
        if (disk[i] != NULL) {
            char disk_number[3];
            memset(buf, '\0', LINEMAX);
            strncat(buf, "(hd", LINEMAX);
            snprintf(disk_number, 3, "%d", i);
            strncat(buf, disk_number, LINEMAX);
            strncat(buf, ") ", LINEMAX);
            strncat(buf, disk[i], LINEMAX);
            fprintf(fp, "%s", buf);
        }
    }

    fclose(fp);
    return 0;
}

int main(int argc, char *argv[])
{
    adjust_grub_device_map(argv[1]);
}
