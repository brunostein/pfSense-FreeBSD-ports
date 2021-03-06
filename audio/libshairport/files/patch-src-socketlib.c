--- src/socketlib.c.orig	2011-09-23 22:00:48.000000000 +0200
+++ src/socketlib.c	2012-10-09 12:09:33.000000000 +0200
@@ -48,7 +48,7 @@
   if((tSock==-1) && (pAddrInfo->ai_family == AF_INET6) && (errno == EAFNOSUPPORT))
   {
     //Fallback to ipv4
-    perror("Failed to create ipv6 socket. Trying ipv4");
+    xprintf("Failed to create ipv6 socket. Trying ipv4");
     pAddrInfo->ai_family = AF_INET;
     tSock = socket(pAddrInfo->ai_family, pAddrInfo->ai_socktype, 0);
   }
@@ -82,7 +82,7 @@
       delay(RETRY_DELAY, &tRes);
     }
   }
-  printf("%d Retry attempts exceeded\n", RETRY_COUNT);
+  xprintf("%d Retry attempts exceeded\n", RETRY_COUNT);
   return ERROR;
 }
 
@@ -102,7 +102,7 @@
   tError = getaddrinfo(pHostname, pService, &hints, pAddrInfo);
   if(tError != 0)
   {
-    printf("Error getting address info\n");
+    xprintf("Error getting address info\n");
   }
   return tError;
 }
@@ -158,8 +158,8 @@
     sprintf(tService, "%d", pPort); // copies port to string
     int tFamily = AF_INET;
     #ifdef AF_INET6
-    //printf("Listening on IPv6 Socket\n");
-    //tFamily = AF_INET6;
+    xprintf("Listening on IPv6 Socket\n");
+    tFamily = AF_INET6;
     #else
     //printf("Listening on IPv4 Socket");
     #endif
@@ -200,7 +200,7 @@
   else
   {
     // Invalid encoded data, no other cases are possible.
-    printf("Unrecoverable error....base64 values are incorrectly encoded\n");
+    xprintf("Unrecoverable error....base64 values are incorrectly encoded\n");
     return pSize;
   }
 }
@@ -226,7 +226,7 @@
     memset(input, 0, length);
     memcpy(input, pInput, pLength);
     memset(input+pLength, '=', length-pLength);
-    printf("Fixed value: [%.*s]\n", length, input);
+    xprintf("Fixed value: [%.*s]\n", length, input);
   }
   char *buffer = (char *)malloc(length);
   memset(buffer, 0, length);
