$(document).ready(function () {
    if (islock) {
        $("#comment_form").html("<div class='notice'>该文章已被禁止评论！</div>");
    } else if (currentUserName) {
        var html = '<a name="commentbox"></a><a name="reply"></a><a name="quote"></a><form action="/' + username + '/comment/submit?id=' + fileName + '" method="post">' +
		'<div class="commentform"><div class="panel_head">发表评论' +
		'</div>' +
		'<ul><li class="left">用 户 名：</li><li class="right">' + currentUserName + '</li></ul>' +
		'<ul><li class="left">评论内容：</li><li class="right" style="position:relative;">' +
		'<div id="ubbtools">' +
        //'<a href="#insertcode" code="code">插入代码</a>'+
		'<a href="#insertcode" code="code"><img src="' + static_host + '/images/ubb/code.gif" border="0" alt="插入代码" title="插入代码"/></a>' +
		'</div>' +
		'<div id="lang_list" style="display:none; position:absolute;top:25px; left:0px;"></div>' +
		'<textarea class="comment_content" name="comment_content" id="comment_content" style="width: 400px; height: 200px;"></textarea>' +
		'</li></ul>' +
        //'<ul id="panel_verifycode" style="display:none;"><li class="left">验 证 码：</li>'+
        //'<li class="right"><span></span> <a id="a_verifycode" href="#verifycode">看不清，换一张</a><br />'+
        //'<input type="text" id="comment_verifycode" id="comment_verifycode" style="width: 60px;" /></li></ul>'+
		'<ul><input type="hidden" id="comment_replyId" name="comment_replyId" />' +
		'<input type="hidden" id="comment_userId" name="comment_userId" value="521203" />' +
		'<input type="hidden" id="commentId" name="commentId" value="" />' +
		'<input type="submit" class="comment_btn" value="提交" />&nbsp;&nbsp;<span id="tip_comment" style="color: Red; display: none;"></span>' +
		'</ul></div></form>';
        $("#comment_form").html(html);
    } else {
        var curl = encodeURIComponent(location.href);
        $("#comment_form").html('<div class="guest_link">您还没有登录,请' +
		'<a href="http://passport.csdn.net/account/login?from=' + curl + '">[登录]</a>或' +
		'<a href="http://passport.csdn.net/account/register?from=' + curl + '">[注册]</a></div>');
    }
    var editorId = "#comment_content";
    editor = $(editorId);
    var verifycodeId = "#img_verifycode";
    var editor_inter = null;
    if (editor.length > 0) {
        var v = ["html", "javascript", "css", "php", "csharp", "cpp", "java", "python", "ruby", "vb", "delphi", "sql", "plain"];
        var k = ["HTML/XML", "JavaScript", "CSS", "PHP", "C#", "C++", "Java", "Python", "Ruby", "Visual Basic", "Delphi", "SQL", "其它"];
        for (var i = 0; i < v.length; i++) {
            $("#lang_list").append('<a href="#' + v[i] + '">' + k[i] + '</a>')
        }
        editor.focus(function () {
            editor_inter = setInterval(function () {
                commentTip("还能输入" + (1000 - editor.val().length) + "个字符");
            }, 200);
        }).blur(function () {
            if (editor_inter) clearInterval(editor_inter);
        });
    }


    //加载列表
    var listId = "#comment_list";
    loadList();
    function noComments() {
        $(listId).html('<br />&nbsp;&nbsp;暂无评论<br /><br /><div class="clear"></div>');
    }
    function loadList(pageIndex) {
        if (commentscount == 0) {
            noComments();
            return;
        }
        pageIndex = parseInt(pageIndex) || 1;

        $("#comments_bar").html("正在加载评论...")
        $.get("../../comment/list/" + fileName + "?page=" + (pageIndex || 1) + "&_" + Math.random(), function (json) {

            if (json == "") {
                noComments();
                return;
            }
            var data = eval("(" + json + ")");
            var list = data.list;
            var listHtml = '';

            //构造主题
            var topics = getTopics(list);

            //组装HTM
            for (var i = 0; i < topics.length; i++) {
                var comment = topics[i];
                var layer = data.page.RecordCount > 0 ? (data.page.RecordCount - (pageIndex - 1) * data.page.PageSize - i) : topics.length - i;
                listHtml += getItemHtml(comment, layer);
            };

            //输出列表
            listHtml += '<div class="clear"></div>';
            if (pageIndex == 1) {
                $(listId).html(listHtml);
            } else {
                $(listId).append(listHtml);
            }
            dp.SyntaxHighlighter.HighlightAll('code2');
            //分页处理

            if (data.page.RecordCount == 0 || (data.page.RecordCount > 0 && data.page.PageSize != topics.length)) {
                $("#comment_bar").html("").hide();
            } else {
                $("#comment_bar").html('<div id="load_comments" page="' + (pageIndex + 1) + '">查看更多评论</div>')
                //$(listId).append(getPageHtml(data.page.PageIndex, data.page.PageSize, data.page.RecordCount));
                //setPageAction();
            }

            $("#load_comments").click(function () {
                var page = $(this).attr("page");
                loadList(page);
            });

            //评论按钮点击
            $(".comment_head a").click(function () {
                var action = $(this).attr("href");

                action = action.substring(action.lastIndexOf('#'));

                var commentId = $(this).parent().attr("commentid");
                switch (action) {
                    case "#reply":
                        if (currentUserName) {
                            commentId = $(".comment_manage", $(this).parent()).attr("commentid");
                            replyComment(commentId, list);
                            editor.focus();
                        }
                        return true;
                    case "#quote":
                        if (currentUserName) {
                            quoteComment(commentId, list);
                            editor.focus();
                        }
                        return true;
                    case "#report":
                        reportComment(commentId, this);

                        break;
                    case "#delete":
                        deleteComment(commentId);
                        break;
                    default:
                        return true;
                }
                return false;
            });

            $(".comment_item").mouseover(function () {
                $(".comment_manage", $(this)).eq(0).show();
            }).mouseout(function () {
                $(".comment_manage", $(this)).eq(0).hide();
            });
        });
    };
    //获取评论主题
    function getTopics(list) {
        var topics = [];
        for (var i = 0; i < list.length; i++) {
            var t = list[i];
            if (t.ParentId === 0) {
                t.Replies = getReplies(t, list);
                topics.push(t);
            }
        }
        return topics;
    }
    //获取评论回复
    function getReplies(topic, list) {
        var replies = [];
        for (var i = 0; i < list.length; i++) {
            var r = list[i];
            if (r.ParentId == topic.CommentId) {
                r.Replies = getReplies(r, list);
                replies.push(r);
            }
        }
        return replies;
    }
    //获取评论的HTML
    function getItemHtml(comment, index, floor) {
        var html = '<dl class="comment_item comment_' + (comment.ParentId > 0 ? "reply" : "topic") + '" id="comment_item_{id}">' +
		'<dt class="comment_head" floor=' + (floor || index) + '>' + (comment.ParentId > 0 ? "Re:" : /*'<a name="comment'+comment.CommentId+'">'+*/index + '楼') + ' <span class="user">';

        if (comment.UserName != null && comment.UserName != '')
            html += '<a class="username" href="/' + comment.UserName + '" target="_blank">' + comment.UserName + '</a>';
        else
            html += '[游客]';

        html += " <span class='ptime'>" + comment.PostTime + "发表</span> ";
        html += ' <a href="#reply" class="cmt_btn reply" title="回复">[回复]</a> <span class="comment_manage" style="display:none;" commentid={id} username={username}> <a href="#quote" class="cmt_btn quote" title="引用">[引用]</a> <a href="#report" class="cmt_btn report" title="举报">[举报]</a>';
        if (username == currentUserName || comment.UserName == currentUserName) html += ' <a href="#delete" class="cmt_btn delete" title="删除">[删除]</a>';
        html += '</span></dt>';
        html += '<dd class="comment_userface"><a href="/' + comment.UserName + '" target="_blank"><img src="' + comment.Userface + '" width="40" height="40" /></a></dd>';
        html += '<dd class="comment_body">' + replaceUBBToHTML(comment) + '</dd>';
        html = html.replace(/\{id\}/g, comment.CommentId).replace(/\{username\}/g, comment.UserName);

        if (comment.Replies != null) {
            for (var j = 0; j < comment.Replies.length; j++) {
                html += getItemHtml(comment.Replies[j], j + 1, index);
            }
        }
        html += "</dl>";

        return html;
    }
    //获取评论对象
    function getComment(commentId, list) {
        for (var i = 0; i < list.length; i++) {
            var comment = list[i];
            if (comment.CommentId == commentId)
                return comment;
        }
        return null;
    }
    //引用评论
    function quoteComment(commentId, list) {
        var comment = getComment(commentId, list);
        var content = comment.Content;
        if (comment.Content.length > 50) {
            content = comment.Content.substring(0, 50) + "...";
        }
        editor.val("[quote=" + (comment.UserName == null ? "游客" : comment.UserName) + "]" + content + "[/quote]\r\n");
    }
    //回复评论
    function replyComment(commentId, list) {
        var comment = getComment(commentId, list);
        editor.val('[reply]' + comment.UserName + "[/reply]\r\n");
        $("#comment_replyId").val(commentId);
    }
    //举报评论
    function reportComment(commentId, e) {
        report(commentId, 3, e);
    }
    //删除评论
    function deleteComment(commentId) {
        if (!confirm("你确定要删除这篇评论吗？")) return;
        $.get(blog_address + "/comment/delete?commentid=" + commentId + "&filename=" + fileName, function (data) {
            if (data.result == 1) {
                $("#comment_item_" + commentId).hide().remove();
            }
            else {
                alert("你没有删除该评论的权限！");
            }
        });
    }
    //替换评论的UBB代码
    function replaceUBBToHTML(comment) {
        var content = $.trim(comment.Content);

        var re = /\[code=([\w#\.]+)\]([\s\S]*?)\[\/code\]/ig;

        var codelist = [];
        while ((mc = re.exec(content)) != null) {
            codelist.push(mc[0]);
            content = content.replace(mc[0], "--code--");
        }
        content = replaceQuote(content);
        content = content.replace(/\[e(\d+)\]/g, "<img src=\"" + static_host + "/images/emotions/e$1.gif\"\/>");
        //var emotions = ["顶","砸","棒","大笑","愤怒","大哭","疑问","汗","呕吐","送花"];
        //content = content.replace(/\[e(\d+)\]/g, function(m0,m1){return "["+emotions[parseInt(m1)+1]+"]"});
        //content = content.replace(/\[reply]([\s\S]*?)\[\/reply\]/gi, '<p><a href="#comment'+comment.ParentId+'">@@</a>$1:<br /></p>');
        content = content.replace(/\[reply]([\s\S]*?)\[\/reply\](\n)?/gi, "回复$1：");
        content = content.replace(/\[url=([^\]]+)]([\s\S]*?)\[\/url\]/gi, '<a href="$1" target="_blank">$2</a>');
        content = content.replace(/\[img(=([^\]]+))?]([\s\S]*?)\[\/img\]/gi, '<img src="$3" style="max-width:400px;max-height:200px;" border="0" title="$2" />');
        content = content.replace(/\[(\/?)(b|i|u|p)\]/ig, "<$1$2>");
        content = content.replace(/\n/ig, "<br />");

        if (codelist.length > 0) {
            var re1 = /--code--/ig;
            var i = 0;
            while ((mc = re1.exec(content)) != null) {
                content = content.replace(mc[0], codelist[i]);
                i++;
            }
        }
        content = content.replace(/\[code=([\w#\.]+)\]([\s\S]*?)\[\/code\]/ig, function (m0, m1, m2) { if ($.trim(m2) == "") return ''; return '<pre name="code2" class="' + m1 + '">' + m2 + '</pre>' });
        return content;
    }
    //替换评论的引用
    function replaceQuote(str) {
        var m = /\[quote=([^\]]+)]([\s\S]*)\[\/quote\]/gi.exec(str);
        if (m) {
            return str.replace(m[0], '<fieldset><legend>引用“' + m[1] + '”的评论：</legend>' + replaceQuote(m[2]) + '</fieldset>');
        } else {
            return str;
        }
    }
    //加载编辑器
    //激活验证码
    //editor.focus(function(){
    //	loadVerifyCode();
    //});
    //更换验证码
    //$("#a_verifycode").unbind("click").click(refreshVerifyCode);
    //添加表情
    /*$("#emotions img").click(function () {
    appendToEditor("[" + $(this).attr("code") + "]");
    });*/
    //ubb按钮事件
    $("#ubbtools").children().click(function () {
        var selectedValue = editor.selection();
        editor.focus();
        var code = $(this).attr("code");
        switch (code) {
            /*case "indent":
            editor.val("\t" + selectedValue);
            break;
            case "url":
            var title = prompt("链接标题：","");
            var link = prompt("链接地址：", "http://");
            editor.val("[url=" + link + "]" + title + "[/url]");
            break;*/ 
            case "code":
                var lang_list = $("#lang_list");
                lang_list.show();
                lang_list.children().each(function () {
                    $(this).unbind("click").click(function () {
                        editor.val("[code=" + $.trim(this.href.split('#')[1]) + "]\n" + selectedValue + "\n[/code]");
                        lang_list.hide();
                    });
                });
                editor.click(function (e) {
                    lang_list.hide();
                });
                break;
            default:
                editor.val("[" + code + "]" + selectedValue + "[/" + code + "]");
                break;
        }
        return false;
    });
    //提交事件
    var c_doing = false;
    $("#comment_form > form").submit(function () {
        if (c_doing) return false;
        var content = $.trim($(editorId).val());
        if (content == "") {
            commentTip("评论内容没有填写!");
            return false;
        } else if (content.length > 1000) {
            commentTip("评论内容太长了，不能超过1000个字符！");
            return false;
        }
        /*if($(verifycodeId).length == 0)
        {
        loadVerifyCode();
        return false;
        }*/
        var commentId = $("#commentId").val();
        commentTip("正在发表评论...");
        var beginTime = new Date();
        $(editorId).attr("disabled", true);
        $("button[type=submit]", this).attr("disabled", true);
        c_doing = true;
        $.ajax({
            type: "POST",
            url: $(this).attr("action"),
            data: {
                "commentid": commentId,
                "content": content,
                "replyId": $("#comment_replyId").val()
                //"VerifyCode": $("#comment_verifycode").val()
            },
            success: function (data) {
                c_doing = false;
                commentTip(data.content);
                if (data.result) {
                    $(editorId).val('');
                    $("#comment_replyId,#comment_verifycode").val('');
                    //refreshVerifyCode();
                    commentscount++;
                    loadList();
                    $(editorId).attr("disabled", false);
                    $("button[type=submit]", this).attr("disabled", false);

                    commentTip("发表成功！评论耗时:" + (new Date() - beginTime) + "毫秒")
                }
            }
        });
        return false;
    });

    //操作提示
    var t;
    function commentTip(message) {
        $("#tip_comment").html(message).show();
        clearTimeout(t);
        t = setTimeout(function () {
            $("#tip_comment").hide();
        }, 10000);
    }

    /*function loadVerifyCode() {
    $("#panel_verifycode").show();
    var img = $(verifycodeId);
    if(img.length == 0){
    $("#panel_verifycode span").html('<img id="img_verifycode" border="0" />');
    refreshVerifyCode();
    }
    }
    function refreshVerifyCode(){
    $(verifycodeId).attr('src',blog_address + "/common/verifycode?r=" + Math.random())
    }*/
});